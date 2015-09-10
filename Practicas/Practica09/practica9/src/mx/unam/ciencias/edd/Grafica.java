package mx.unam.ciencias.edd;

import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * Clase para gráficas. Una gráfica es un conjunto de vértices y
 * aristas, tales que las aristas son un subconjunto del producto
 * cruz de los vértices.
 */
public class Grafica<T> implements Iterable<T> {

    /* Clase privada para iteradores de gráficas. */
    private class Iterador<T> implements Iterator<T> {

        /* Iterador auxiliar. */
        private Iterator<Grafica<T>.Vertice<T>> iterador;

        /* Construye un nuevo iterador, auxiliándose de la lista de
         * vértices. */
        public Iterador(Grafica<T> grafica) {
            this.iterador = grafica.vertices.iterator();
        }

        /* Nos dice si hay un siguiente elemento. */
        public boolean hasNext() {
	    return iterador.hasNext();
        }

        /* Regresa el siguiente elemento. */
        public T next() {
	    return iterador.next().elemento;
        }

        /* No lo implementamos: siempre lanza una excepción. */
        public void remove() {
            throw new UnsupportedOperationException();
        }
    }

    /* Aristas para gráficas; para poder guardar el peso de las
     * aristas. */
    private class Arista<T> {

        /* El vecino del vértice. */
        public Grafica<T>.Vertice<T> vecino;
        /* El peso de arista conectando al vértice con el vecino. */
        public double peso;

        public Arista(Grafica<T>.Vertice<T> vecino, double peso) {
            this.vecino = vecino;
            this.peso = peso;
        }
    }

    /* Vertices para gráficas; implementan la interfaz
     * ComparableIndexable y VerticeGrafica */
    private class Vertice<T> implements ComparableIndexable<Vertice<T>>,
        VerticeGrafica<T> {

        /* Iterador para las vecinos del vértice. */
        private class IteradorVecinos implements Iterator<VerticeGrafica<T>> {

            /* Iterador auxiliar. */
            private Iterator<Grafica<T>.Arista<T>> iterador;
            
            /* Construye un nuevo iterador, auxiliándose de la lista
             * de vecinos. */
            public IteradorVecinos(Iterator<Grafica<T>.Arista<T>> iterador) {
                this.iterador = iterador;
            }

            /* Nos dice si hay un siguiente vecino. */
            public boolean hasNext() {
                return iterador.hasNext();
            }

            /* Regresa el siguiente vecino. La audición es
             * inevitable. */
            public VerticeGrafica<T> next() {
                Grafica<T>.Arista<T> arista = iterador.next();
                return (VerticeGrafica<T>)arista.vecino;
            }

            /* No lo implementamos: siempre lanza una excepción. */
            public void remove() {
                throw new UnsupportedOperationException();
            }
        }

        /* El elemento del vértice. */
        public T elemento;
        /* El color del vértice. */
        public Color color;
        /* La distancia del vértice. */
        public double distancia;
        /* El índice del vértice. */
        public int indice;
        /* La lista de aristas que conectan al vértice con sus
         * vecinos. */
        public Lista<Grafica<T>.Arista<T>> aristas;

        /* Crea un nuevo vértice a partir de un elemento. */
        public Vertice(T elemento) {
            this.elemento = elemento;
            color = Color.NINGUNO;
            aristas = new Lista<Grafica<T>.Arista<T>>();
	    distancia = -1;
        }

        /* Regresa el elemento del vértice. */
        public T getElemento() {
	    return elemento;
        }

        /* Regresa el grado del vértice. */
        public int getGrado() {
	    return aristas.getLongitud();
        }

        /* Regresa el color del vértice. */
        public Color getColor() {
	    return color;
        }

        /* Define el color del vértice. */
        public void setColor(Color color) {
	    this.color = color;
        }

        /* Regresa un iterador para los vecinos. */
        public Iterator<VerticeGrafica<T>> iterator() {
            return new IteradorVecinos(aristas.iterator());
        }

        /* Define el índice del vértice. */
        public void setIndice(int indice) {
	    this.indice = indice;
        }

        /* Regresa el índice del vértice. */
        public int getIndice() {
	    return indice;
        }

        /* Compara dos vértices por distancia. */
        public int compareTo(Vertice<T> vertice) {
	    if(distancia != -1 && vertice.distancia == -1)
		return -1;
	    else if(distancia > vertice.distancia)
		return 1;
	    else if(distancia < vertice.distancia)
		return -1;
	    else
		return 0;
	}
    }

    /* Vértices. */
    private Lista<Vertice<T>> vertices;
    /* Número de aristas. */
    private int aristas;

    /**
     * Constructor único.
     */
    public Grafica() {
	this.vertices = new Lista<Vertice<T>>();
	this.aristas = 0;
    }

    /**
     * Regresa el número de vértices.
     * @return el número de vértices.
     */
    public int getVertices() {
	return vertices.getLongitud();
    }

    /**
     * Regresa el número de aristas.
     * @return el número de aristas.
     */
    public int getAristas() {
	return aristas;
    }
    

    /**
     * Agrega un nuevo elemento a la gráfica.
     * @param elemento el elemento a agregar.
     * @throws IllegalArgumentException si el elemento ya había sido
     *         agregado a la gráfica.
     */
    public void agrega(T elemento) {
	Vertice<T> vert = buscaVertice(elemento);
	if(vert == null)
	    vertices.agregaFinal(new Vertice<T>(elemento));
	else
	    throw new IllegalArgumentException();
    }
    
    /**
     * Conecta dos elementos de la gráfica. Los elementos deben
     * estar en la gráfica. El peso de la arista que conecte a los
     * elementos será 1.
     * @param a el primer elemento a conectar.
     * @param b el segundo elemento a conectar.
     * @throws NoSuchElementException si a o b no son elementos de
     *         la gráfica.
     * @throws IllegalArgumentException si a o b ya están
     *         conectados, o si a es igual a b.
     */
    public void conecta(T a, T b) {
	Vertice<T> verticeA = buscaVertice(a);
	Vertice<T> verticeB = buscaVertice(b);
	if(verticeA == null || verticeB == null)
	    throw new NoSuchElementException();
	else if(sonVecinos(a, b) || verticeA == verticeB)
	    throw new IllegalArgumentException();
	else{
	    verticeA.aristas.agregaFinal(new Arista<T>(verticeB, 1));
	    verticeB.aristas.agregaFinal(new Arista<T>(verticeA, 1));
	    aristas++;
	}
    }

    /**
     * Conecta dos elementos de la gráfica. Los elementos deben
     * estar en la gráfica.
     * @param a el primer elemento a conectar.
     * @param b el segundo elemento a conectar.
     * @param peso el peso de la nueva arista.
     * @throws NoSuchElementException si a o b no son elementos de
     *         la gráfica.
     * @throws IllegalArgumentException si a o b ya están
     *         conectados, o si a es igual a b.
     */
    public void conecta(T a, T b, double peso) {
	Vertice<T> verticeA = buscaVertice(a);
	Vertice<T> verticeB = buscaVertice(b);
	if(verticeA == null || verticeB == null)
	    throw new NoSuchElementException();
	else if(sonVecinos(a, b) || verticeA == verticeB)
	    throw new IllegalArgumentException();
	else{
	    verticeA.aristas.agregaFinal(new Arista<T>(verticeB, peso));
	    verticeB.aristas.agregaFinal(new Arista<T>(verticeA, peso));
	    aristas++;
	}
    }

    /**
     * Desconecta dos elementos de la gráfica. Los elementos deben
     * estar en la gráfica y estar conectados entre ellos.
     * @param a el primer elemento a desconectar.
     * @param b el segundo elemento a desconectar.
     * @throws NoSuchElementException si a o b no son elementos de
     *         la gráfica.
     * @throws IllegalArgumentException si a o b no están
     *         conectados.
     */
    public void desconecta(T a, T b) {
	Vertice<T> verticeA = buscaVertice(a);
	Vertice<T> verticeB = buscaVertice(b);
	if(verticeA == null || verticeB == null)
	    throw new NoSuchElementException();
	else if(!sonVecinos(a, b))
	    throw new IllegalArgumentException();
	else{
	    eliminaArista(verticeA, verticeB);
	}
    }

    /**
     * Nos dice si el elemento está contenido en la gráfica.
     * @return <tt>true</tt> si el elemento está contenido en la
     *         gráfica, <tt>false</tt> en otro caso.
     */
    public boolean contiene(T elemento) {
	for(int i = 0; i < vertices.getLongitud(); i++){
	    Vertice<T> verticeC = vertices.get(i);
	    if(verticeC.elemento.equals(elemento))
		return true;
	}
	return false;
    }

    /**
     * Elimina un elemento de la gráfica. El elemento tiene que
     * estar contenido en la gráfica.
     * @param elemento el elemento a eliminar.
     * @throws NoSuchElementException si el elemento no está
     *         contenido en la gráfica.
     */
    public void elimina(T elemento) {
	Vertice<T> vertice = buscaVertice(elemento);        
	if(vertice == null)
	    throw new NoSuchElementException();
	else{
	    for(Arista<T> ar : vertice.aristas){
		eliminaArista(vertice, ar.vecino);
	    }
	    vertices.elimina(vertice);
	}
    }

    /**
     * Nos dice si dos elementos de la gráfica están conectados. Los
     * elementos deben estar en la gráfica.
     * @param a el primer elemento.
     * @param b el segundo elemento.
     * @return <tt>true</tt> si a y b son vecinos, <tt>false</tt> en
     *         otro caso.
     * @throws NoSuchElementException si a o b no son elementos de
     *         la gráfica.
     */
    public boolean sonVecinos(T a, T b) {
	Vertice<T> verticeA = buscaVertice(a);
	Vertice<T> verticeB = buscaVertice(b);
	if(verticeA == null || verticeB == null)
	    throw new NoSuchElementException();
	else{
	    for(Arista<T> ver : verticeA.aristas){
		if(ver.vecino == verticeB)
		    return true;
	    }
	    return false;
	}
    }

    /**
     * Regresa el peso de la arista que comparten los vértices que
     * contienen a los elementos recibidos.
     * @param a el primer elemento.
     * @param b el segundo elemento.
     * @return el peso de la arista que comparten los vértices que
     *         contienen a los elementos recibidos, o -1 si los
     *         elementos no están conectados.
     * @throws NoSuchElementException si a o b no son elementos de
     *         la gráfica.
     */
    public double getPeso(T a, T b) {
        Vertice<T> verticeA = buscaVertice(a);
	Vertice<T> verticeB = buscaVertice(b);
	if(verticeA == null || verticeB == null)
	    throw new NoSuchElementException();
	else{
	    for(Arista<T> ver : verticeA.aristas){
		if(ver.vecino == verticeB)
		    return ver.peso;
	    }
	    return -1;
	}
    }

    /**
     * Regresa el vértice correspondiente el elemento recibido.
     * @throws NoSuchElementException si elemento no es elemento de
     *         la gráfica.
     * @return el vértice correspondiente el elemento recibido.
     */
    public VerticeGrafica<T> vertice(T elemento) {
	return buscaVertice(elemento);
    }

    /**
     * Realiza la acción recibida en cada uno de los vértices de la
     * gráfica, en el orden en que fueron agregados.
     * @param accion la acción a realizar.
     */
    public void paraCadaVertice(AccionVerticeGrafica<T> accion) {
	for(Vertice<T> ver: vertices)
	    accion.actua(ver);
    }

    /**
     * Realiza la acción recibida en todos los vértices de la
     * gráfica, en el orden determinado por BFS, comenzando por el
     * vértice correspondiente al elemento recibido. Al terminar el
     * método, todos los vértices tendrán color {@link
     * Color#NINGUNO}.
     * @param elemento el elemento sobre cuyo vértice queremos
     *        comenzar el recorrido.
     * @param accion la acción a realizar.
     * @throws NoSuchElementException si el elemento no está en la
     *         gráfica.
     */
    public void bfs(T elemento, AccionVerticeGrafica<T> accion) {
	Vertice<T> raiz = buscaVertice(elemento);       
	if(raiz == null)
	    throw new NoSuchElementException();
	else{
	    Cola<Grafica<T>.Vertice<T>> cola = new Cola<Grafica<T>.Vertice<T>>();
	    raiz.setColor(Color.ROJO);
	    cola.mete(raiz);
	    while(!cola.esVacia()){
		Vertice<T> temp = cola.saca();
		accion.actua(temp);
		for(Arista<T> ver : temp.aristas){
		    if(ver.vecino.color != Color.ROJO){
			ver.vecino.color = Color.ROJO;
			cola.mete(ver.vecino);
		    }
		}
		if(cola.esVacia()){
		    for(int i = 0; i < vertices.getLongitud(); i++){
			temp = vertices.get(i);
			if(temp.color != Color.ROJO){
			    for(Arista<T> ver : temp.aristas){
				if(ver.vecino.color != Color.ROJO){
				    ver.vecino.color = Color.ROJO;
				    cola.mete(ver.vecino);
				}
			    }   
			}
		    }
		}
	    }
	    for(Vertice<T> ver : vertices){
		ver.setColor(Color.NINGUNO);
	    }
	}
    }

    /**
     * Realiza la acción recibida en todos los vértices de la
     * gráfica, en el orden determinado por DFS, comenzando por el
     * vértice correspondiente al elemento recibido. Al terminar el
     * método, todos los vértices tendrán color {@link
     * Color#NINGUNO}.
     * @param elemento el elemento sobre cuyo vértice queremos
     *        comenzar el recorrido.
     * @param accion la acción a realizar.
     * @throws NoSuchElementException si el elemento no está en la
     *         gráfica.
     */
    public void dfs(T elemento, AccionVerticeGrafica<T> accion) {
	Vertice<T> raiz = buscaVertice(elemento);       
	if(raiz == null)
	    throw new NoSuchElementException();
	else{
	    Pila<Grafica<T>.Vertice<T>> pila = new Pila<Grafica<T>.Vertice<T>>();
	    raiz.setColor(Color.ROJO);
	    pila.mete(raiz);
	    while(!pila.esVacia()){
		Vertice<T> temp = pila.saca();
		accion.actua(temp);
		for(Arista<T> ver : temp.aristas){
		    if(ver.vecino.color != Color.ROJO){
			ver.vecino.color = Color.ROJO;
			pila.mete(ver.vecino);
		    }
		}
		if(pila.esVacia()){
		    for(int i = 0; i < vertices.getLongitud(); i++){
			temp = vertices.get(i);
			if(temp.color != Color.ROJO){
			    for(Arista<T> ver : temp.aristas){
				if(ver.vecino.color != Color.ROJO){
				    ver.vecino.color = Color.ROJO;
				    pila.mete(ver.vecino);
				}
			    }   
			}
		    }
		}
	    }
	    for(Vertice<T> ver : vertices){
		ver.setColor(Color.NINGUNO);
	    }
	}
    }

    /**
     * Regresa un iterador para iterar la gráfica. La gráfica se
     * itera en el orden en que fueron agregados sus elementos.
     * @return un iterador para iterar el árbol.
     */
    @Override public Iterator<T> iterator() {
        return new Iterador<T>(this);
    }

    /**
     * Calcula una trayectoria de distancia mínima entre dos
     * vértices.
     * @param origen el vértice de origen.
     * @param destino el vértice de destino.
     * @return Una lista con vértices de la gráfica, tal que forman
     *         una trayectoria de distancia mínima entre los
     *         vértices <tt>a</tt> y <tt>b</tt>. Si los elementos se
     *         encuentran en componentes conexos distintos, el
     *         algoritmo regresa una lista vacía.
     * @throws NoSuchElementException si alguno de los dos elementos
     *         no está en la gráfica.
     */
    public Lista<VerticeGrafica<T>> trayectoriaMinima(T origen, T destino) {
	Lista<VerticeGrafica<T>> ret = new Lista<VerticeGrafica<T>>();
	Grafica<T> temp = this;
	Vertice<T> verticeA = temp.buscaVertice(origen);
	Vertice<T> verticeB = temp.buscaVertice(destino);
	if(verticeA == null || verticeB == null)
	    throw new NoSuchElementException();
	else{
	    Vertice<T> verTemp = verticeA;
	    MonticuloMinimo<Grafica<T>.Vertice<T>> monticulo = new MonticuloMinimo<Grafica<T>.Vertice<T>>();	    
	    verTemp.distancia = 0;
	    monticulo.agrega(verTemp);
	    verTemp.setColor(Color.ROJO);
	    while(!monticulo.esVacio()){
		verTemp = monticulo.elimina();
		for(Arista<T> ari : verTemp.aristas){
		    if((verTemp.distancia+1 < ari.vecino.distancia
			|| ari.vecino.distancia == -1)){
			ari.vecino.distancia = (verTemp.distancia+1);
			monticulo.agrega(ari.vecino);
			ari.vecino.setColor(Color.ROJO);
		    }
		}
	    }
	    if(verticeB.getColor() != Color.ROJO)
		return ret;
	    verTemp = temp.buscaVertice(origen);
	    ret.agregaInicio(verticeB);
	    while(verticeA != verticeB){
		for(Arista<T> ari : verticeB.aristas){
		    if(verticeB.distancia - 1 == ari.vecino.distancia){
			verticeB = ari.vecino;
			ret.agregaInicio(verticeB);
			break;
		    }
		}
	    }
	}
	for(Grafica<T>.Vertice<T> ver : temp.vertices){
	    ver.distancia =-1;
	    ver.setColor(Color.NINGUNO);
	}
	return ret;
    }
    /**
     * Calcula la ruta de peso mínimo entre el elemento de origen y
     * el elemento de destino.
     * @param origen el vértice origen.
     * @param destino el vértice destino.
     * @return una trayectoria de peso mínimo entre el vértice
     *         <tt>origen</tt> y el vértice <tt>destino</tt>. Si los
     *         vértices están en componentes conexas distintas,
     *         regresa una lista vacía.
     * @throws NoSuchElementException si alguno de los dos elementos
     *         no está en la gráfica.
     */
    public Lista<VerticeGrafica<T>> dijkstra(T origen, T destino) {
	Lista<VerticeGrafica<T>> ret = new Lista<VerticeGrafica<T>>();
	Grafica<T> temp = this;
	Vertice<T> verticeA = temp.buscaVertice(origen);
	Vertice<T> verticeB = temp.buscaVertice(destino);
	if(verticeA == null || verticeB == null)
	    throw new NoSuchElementException();
	else{
	    Vertice<T> verTemp = verticeA;
	    MonticuloMinimo<Grafica<T>.Vertice<T>> monticulo = new MonticuloMinimo<Grafica<T>.Vertice<T>>();	    
	    verTemp.distancia = 0;
	    monticulo.agrega(verTemp);
	    verTemp.setColor(Color.ROJO);
	    //for(Grafica<T>.Vertice<T> ver : temp.vertices){ System.out.println("vertice "+ ver.elemento+ " y su indice: "+ ver.getIndice());}
	    while(!monticulo.esVacio()){
		verTemp = monticulo.elimina();
		for(Arista<T> ari : verTemp.aristas){
		    //System.out.println("Estoy en "+verTemp.elemento+" (cuyo peso es:" +verTemp.distancia+ ") y voy a "+ari.vecino.elemento +"(cuyo peso es:" +ari.vecino.distancia+") por la arista de peso " +ari.peso);
		    if((verTemp.distancia+ari.peso < ari.vecino.distancia
			|| ari.vecino.distancia == -1)){
			//System.out.println("Tenía este peso mi vertice "+ari.vecino.distancia);
			ari.vecino.distancia = (verTemp.distancia+ari.peso);
			monticulo.agrega(ari.vecino);
			ari.vecino.setColor(Color.ROJO);
			//System.out.println("Y ahora tiene este "+ari.vecino.distancia);
		    }
		}
	    }
	    if(verticeB.getColor() != Color.ROJO)
		return ret;
	    verTemp = temp.buscaVertice(origen);
	    ret.agregaInicio(verticeB);
	    while(verticeA != verticeB){
		for(Arista<T> ari : verticeB.aristas){
		    if(verticeB.distancia - ari.peso == ari.vecino.distancia){
			verticeB = ari.vecino;
			ret.agregaInicio(verticeB);
			break;
		    }
		}
	    }
	}
	/*for(int i = 0; i < ret.getLongitud(); i++)
	  System.out.println(ret.get(i).getElemento());*/
	for(Grafica<T>.Vertice<T> ver : temp.vertices){
	    ver.distancia =-1;
	    ver.setColor(Color.NINGUNO);
	}
	return ret;
    }
    
    /**
     * Metodo privado que busca un vertice dado un elemento.
     * @param elemento - es el elemento que contiene el vertice.
     * @return el vertice que contiene ese elemento.
     */
    private Vertice<T> buscaVertice(T elemento) {
	for(int i = 0; i < vertices.getLongitud(); i++){
	    Vertice<T> buscaVer = vertices.get(i);
	    if(buscaVer.elemento.equals(elemento))
		return buscaVer;
	}
	return null;
    }
    
    /**
     * Metodo privado para eliminar una arista.
     * @param verticeA - es el primer vertice de la arista.
     * @param verticeB - es el segundo vertice de la arista.
     */
    private void eliminaArista(Vertice<T> verticeA, Vertice<T> verticeB){
	if(verticeA == null || verticeB == null)
	    return;
	if(!sonVecinos(verticeA.elemento, verticeB.elemento))
	    return;
	Arista<T> a1 = null;
	Arista<T> a2 = null;
	for(Arista<T> ver : verticeA.aristas){
	    if(ver.vecino == verticeB)
		a1 = ver; break;
	}
	for(Arista<T> ver : verticeB.aristas){
	    if(ver.vecino == verticeA)
		a2 = ver; break;
	}
	verticeA.aristas.elimina(a1);
	verticeB.aristas.elimina(a2);
	aristas--;
    }
    
} //Fin de Grafica.java.