package mx.unam.ciencias.edd;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Clase para diccionarios (<em>hash tables</em>). Un diccionario
 * generaliza el concepto de arreglo, permitiendo (en general,
 * dependiendo de qué tan buena sea su método para generar huellas
 * digitales) agregar, eliminar, y buscar valores en <i>O</i>(1) en
 * cada uno de estos casos.
 */
public class Diccionario<K, V> implements Iterable<V> {

    /* Clase privada para iteradores de diccionarios. */
    private class Iterador<V> implements Iterator<V> {

        /* En qué lista estamos. */
        private int indice;
        /* Diccionario. */
        private Diccionario<K,V> diccionario;
        /* Iterador auxiliar. */
        private Iterator<Diccionario<K,V>.Entrada<K,V>> iterador;

        /* Construye un nuevo iterador, auxiliándose de las listas
         * del diccionario. */
        public Iterador(Diccionario<K,V> diccionario) {
	    indice = 0;
	    this.diccionario = diccionario;
	    while(indice < diccionario.entradas.length && diccionario.entradas[indice] == null)
		indice++;
	    if(indice < diccionario.entradas.length)
		iterador = diccionario.entradas[indice].iterator();
        }
	
        /* Nos dice si hay un siguiente elemento. */
        public boolean hasNext() {
	    if(iterador == null)
		return false;
	    if(iterador.hasNext())
		return true;
	    int temp = indice;
	    do{
		indice++;
	    }while(indice < diccionario.entradas.length && diccionario.entradas[indice] == null);
	    if(indice >= diccionario.entradas.length){
		indice = temp;
		return false;
	    }if(diccionario.entradas[indice] != null){
		indice = temp;
		return true;	   	    
	    }
	    return false;
        }
	
        /* Regresa el siguiente elemento. */
        public V next() {
	    if(!hasNext())
		throw new NoSuchElementException();
	    if(iterador.hasNext())
		return iterador.next().valor;
	    do{
		indice++;
	    }while(indice < diccionario.entradas.length && diccionario.entradas[indice] == null);
	    iterador = diccionario.entradas[indice].iterator();
	   return iterador.next().valor;
        }

        /* No lo implementamos: siempre lanza una excepción. */
        public void remove() {
            throw new UnsupportedOperationException();
        }
    }

    /** Máxima carga permitida por el diccionario. */
    public static final double MAXIMA_CARGA = 0.72;

    /* Tamaño mínimo; decidido arbitrariamente a 2^6. */
    private static final int MIN_N = 64;

    /* Máscara para no usar módulo. */
    private int mascara;
    /* Huella digital. */
    private HuellaDigital<K> huella;
    /* Nuestro diccionario. */
    private Lista<Entrada<K, V>>[] entradas;
    /* Número de valores*/
    private int total;

    /* Clase para las entradas del diccionario. */
    private class Entrada<K, V> {
        public K llave;
        public V valor;
        public Entrada(K llave, V valor) {
            this.llave = llave;
            this.valor = valor;
        }
    }

    /* Truco para crear un arreglo genérico. Es necesario hacerlo
       así por cómo Java implementa sus genéricos; de otra forma
       obtenemos advertencias del compilador. */
    @SuppressWarnings("unchecked") private Lista<Entrada<K, V>>[] nuevoArreglo(int n) {
        Lista[] arreglo = new Lista[n];
        return (Lista<Entrada<K, V>>[])arreglo;
    }

    /**
     * Construye un diccionario con un tamaño inicial y huella
     * digital predeterminados.
     */
    public Diccionario() {
	this(MIN_N, new HuellaDigital<K>(){
		@Override
		public int huellaDigital(K llave){
		    return llave.hashCode();
		}
	    });
    }

    /**
     * Construye un diccionario con un tamaño inicial definido por
     * el usuario, y una huella digital predeterminada.
     * @param tam el tamaño a utilizar.
     */
    public Diccionario(int tam) {
	this(tam, new HuellaDigital<K>(){
 		@Override
		public int huellaDigital(K llave){
		    return llave.hashCode();
		}
	    });
    }

    /**
     * Construye un diccionario con un tamaño inicial
     * predeterminado, y una huella digital definida por el usuario.
     * @param huella la huella digital a utilizar.
     */
    public Diccionario(HuellaDigital<K> huella) {
	this(MIN_N, huella);
    }

    /**
     * Construye un diccionario con un tamaño inicial, y un método
     * de huella digital definidos por el usuario.
     * @param tam el tamaño del diccionario.
     * @param huella la huella digital a utilizar.
     */
    public Diccionario(int tam, HuellaDigital<K> huella) {
	if(tam < MIN_N)
	    tam = MIN_N;
	this.huella = huella;
	mascara = sacaMascara(tam);
	entradas = nuevoArreglo(mascara+1);
	total = 0;
    }

    /**
     * Agrega un nuevo valor al diccionario, usando la llave
     * proporcionada. Si la llave ya había sido utilizada antes para
     * agregar un valor, el diccionario reemplaza ese valor con el
     * recibido aquí.
     * @param llave la llave para agregar el valor.
     * @param valor el valor a agregar.
     */
    public void agrega(K llave, V valor) {
	int indice = indice(llave);
	Lista<Entrada<K,V>> lista = getLista(indice, true);
	Entrada<K,V> entrada = buscaEntrada(lista, llave);
	if(entrada != null)
	    entrada.valor = valor;
	else{
	    entrada = new Entrada<K,V>(llave, valor);
	    lista.agregaFinal(entrada);
	    total++;
	}
	if(carga() > MAXIMA_CARGA)
	    creceArreglo();
    }

    /**
     * Regresa el valor del diccionario asociado a la llave
     * proporcionada.
     * @param llave la llave para buscar el valor.
     * @return el valor correspondiente a la llave.
     * @throws <tt>NoSuchElementException</tt> si la llave no está
     *         en el diccionario.
     */
    public V get(K llave) {
	int indice = indice(llave);
	Lista<Entrada<K,V>> lista = getLista(indice, false);
	if(lista == null)
	    throw new NoSuchElementException();
	Entrada<K,V> entrada = buscaEntrada(lista, llave);
	if(entrada == null)
	    throw new NoSuchElementException();
	return entrada.valor;
    }

    /**
     * Nos dice si una llave se encuentra en el diccionario.
     * @param llave la llave que queremos ver si está en el diccionario.
     * @return <tt>true</tt> si la llave está en el diccionario,
     *         <tt>false</tt> en otro caso.
     */
    public boolean contiene(K llave) {
	int indice = indice(llave);
	Lista<Entrada<K,V>> lista = getLista(indice, false);
	if(lista == null)
	    return false;
	Entrada<K,V> entrada = buscaEntrada(lista, llave);
	if(entrada == null)
	    return false;
	return true;
    }

    /**
     * Elimina el valor del diccionario asociado a la llave
     * proporcionada.
     * @param llave la llave para buscar el valor a eliminar.
     * @throws NoSuchElementException si la llave no se encuentra en
     *         el diccionario.
     */
    public void elimina(K llave) {
	int indice = indice(llave);
	Lista<Entrada<K,V>> lista = getLista(indice, false);
	if(lista == null)
	    return;
	Entrada<K,V> entrada = buscaEntrada(lista, llave);
	if(entrada == null)
	    return;
	lista.elimina(entrada);
	total--;
	if(lista.getLongitud() == 0)
	    entradas[indice] = null;
    }

    /**
     * Regresa una lista con todas las llaves con valores asociados
     * en el diccionario. La lista no tiene ningún tipo de orden.
     * @return una lista con todas las llaves.
     */
    public Lista<K> llaves() {
	Lista<K> lista = new Lista<K>();
	for(int i = 0; i < entradas.length; i++){
	    if(entradas[i] != null){
		int j = 0;		  
		while(j < entradas[i].getLongitud()){
		    lista.agregaFinal(entradas[i].get(j).llave);
		    j++;
		}
	    }
	}
	return lista;
    }

    /**
     * Regresa una lista con todos los valores en el diccionario. La
     * lista no tiene ningún tipo de orden.
     * @return una lista con todos los valores.
     */
    public Lista<V> valores() {
	Lista<V> lista = new Lista<V>();
	for(int i = 0; i < entradas.length; i++){
	    if(entradas[i] != null){
		int j = 0;		  
		while(j < entradas[i].getLongitud()){
		    lista.agregaFinal(entradas[i].get(j).valor);
		    j++;
		}
	    }
	}
	return lista;
    }
 

    /**
     * Nos dice el máximo número de colisiones para una misma llave
     * que tenemos en el diccionario.
     * @return el máximo número de colisiones para una misma llave.
     */
    public int colisionMaxima() {
	int max = 0;
	for(int i = 0; i < entradas.length; i++){
	    if(entradas[i] != null)		  
		if(entradas[i].getLongitud()-1 > max)
		    max = entradas[i].getLongitud()-1;
	}
	return max;
    }

    /**
     * Nos dice cuántas colisiones hay en el diccionario.
     * @return cuántas colisiones hay en el diccionario.
     */
    public int colisiones() {
	int colisiones = 0;
	for(int i = 0; i < entradas.length; i++){
	    if(entradas[i] != null)		  
		if(entradas[i].getLongitud()-1 > 0)
		    colisiones += entradas[i].getLongitud()-1;
	}
	return colisiones;
    }

    /**
     * Nos dice la carga del diccionario.
     * @return la carga del diccionario.
     */
    public double carga() {
	double carga = (total)/(double)(mascara+1);
	return carga;
    }

    /**
     * Regresa el número de valores en el diccionario.
     * @return el número de valores en el diccionario.
     */
    public int getTotal() {
	return total;
    }

    /**
     * Regresa un iterador para iterar los valores del
     * diccionario. El diccionario se itera sin ningún orden
     * específico.
     * @return un iterador para iterar el diccionario.
     */
    @Override public Iterator<V> iterator() {
        return new Iterador<V>(this);
    }
    
    //Metodo privado para sacar el índice de la entrada.
    private int indice(K llave){
	return mascara & huella.huellaDigital(llave);
    }    
    
    //Metodo privado para optener la lista donde se encuentra la entrada.
    private Lista<Entrada<K,V>> getLista(int indice, boolean estado){
	if(indice >= entradas.length)
	    return null;
	if(entradas[indice] == null && estado){
	    Lista<Entrada<K,V>> lista = new Lista<Entrada<K,V>>();
	    entradas[indice] = lista;
	    return lista;
	}else{
	    return entradas[indice];
	}
    }    

    //Metodo privado para crecer un arreglo.
    private void creceArreglo(){
	Lista<Entrada<K,V>>[] nueva = nuevoArreglo(entradas.length*2);
	mascara += 1;
	mascara *= 2;
	mascara -= 1;
	for(int i = 0; i < entradas.length; i++){
	    if(entradas[i] != null){
		int j = 0;		  
		while(j < entradas[i].getLongitud()){
		    nueva[(indice(entradas[i].get(j).llave))] 
			= agregaNuevo(nueva[indice(entradas[i].get(j).llave)], entradas[i].get(j));
		    j++;
		}
	    }
	}
	entradas = nueva;
    }

    //Metodo privado para agregar dar una nueva lista con una entrada.
    private Lista<Entrada<K,V>> agregaNuevo(Lista<Entrada<K,V>> vieja, Entrada<K,V> entrada) {
	Lista<Entrada<K,V>> nueva = vieja; 
	if(vieja == null){
	    nueva = new Lista<Entrada<K,V>>();
	}
	nueva.agregaFinal(entrada);
	return nueva;	
    }

    //Metodo privado para buscar una entrada en una lista.
    private Entrada<K,V> buscaEntrada(Lista<Entrada<K,V>> lista, K llave){
	if(lista == null)
	    return null;
	for(Entrada<K,V> ent : lista){
	    if(ent.llave.equals(llave))
		return ent;
	}
	return null;
    }

    //Metodo privado para sacar la máscara.
    private int sacaMascara(int tam){
	int i = 0;
	tam = tam << 1;
	int j = tam;
	while(tam != 0){
	    i = i | tam;
	    tam = tam >>> 1;
	}
	return i;
    }
} //Fin de Diccionario.java