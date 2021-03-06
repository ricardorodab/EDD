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

        /* Construye un nuevo iterador, auxiliándose del diccionario
         * de vértices. */
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

            /* Construye un nuevo iterador, auxiliándose del
             * diccionario de vecinos. */
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
        /* El diccionario de aristas que conectan al vértice con sus
         * vecinos. */
        public Diccionario<T, Grafica<T>.Arista<T>> aristas;

        /* Crea un nuevo vértice a partir de un elemento. */
        public Vertice(T elemento) {
            this.elemento = elemento;
            color = Color.NINGUNO;
            aristas = new Diccionario<T, Grafica<T>.Arista<T>>();
	    distancia = -1;
        }

        /* Regresa el elemento del vértice. */
        public T getElemento() {
	    return elemento;
        }

        /* Regresa el grado del vértice. */
        public int getGrado() {
	    return aristas.getTotal();
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
    private Diccionario<T, Vertice<T>> vertices;
    /* Número de aristas. */
    private int aristas;

    /**
     * Constructor único.
     */
    public Grafica() {
	this.vertices = new Diccionario<T, Vertice<T>>();
	this.aristas = 0;     
    }

    /**
     * Regresa el número de vértices.
     * @return el número de vértices.
     */
    public int getVertices() {
	return vertices.getTotal();
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
	if(!vertices.contiene(elemento))
	    vertices.agrega(elemento, new Vertice<T>(elemento));
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
	if(!(vertices.contiene(a) && vertices.contiene(b)))
	    throw new NoSuchElementException();
	Vertice<T> verticeA = vertices.get(a);
	Vertice<T> verticeB = vertices.get(b);
        if(sonVecinos(a, b) || verticeA == verticeB)
	    throw new IllegalArgumentException();
	else{
	    verticeA.aristas.agrega(b, new Arista<T>(verticeB, 1));
	    verticeB.aristas.agrega(a, new Arista<T>(verticeA, 1));
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
	if(!(vertices.contiene(a) && vertices.contiene(b)))
	    throw new NoSuchElementException();
	Vertice<T> verticeA = vertices.get(a);
	Vertice<T> verticeB = vertices.get(b);
        if(sonVecinos(a, b) || verticeA == verticeB)
	    throw new IllegalArgumentException();
	else{
	    verticeA.aristas.agrega(b, new Arista<T>(verticeB, peso));
	    verticeB.aristas.agrega(a, new Arista<T>(verticeA, peso));
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
	if(!(vertices.contiene(a) && vertices.contiene(b)))
	    throw new NoSuchElementException();
	Vertice<T> verticeA = vertices.get(a);
	Vertice<T> verticeB = vertices.get(b);
	if(!sonVecinos(a, b))
	    throw new IllegalArgumentException();
	else{
	    verticeA.aristas.elimina(b);
	    verticeB.aristas.elimina(a);
	    aristas--;
	}
    }

    /**
     * Nos dice si el elemento está contenido en la gráfica.
     * @return <tt>true</tt> si el elemento está contenido en la
     *         gráfica, <tt>false</tt> en otro caso.
     */
    public boolean contiene(T elemento) {
	return vertices.contiene(elemento);
    }

    /**
     * Elimina un elemento de la gráfica. El elemento tiene que
     * estar contenido en la gráfica.
     * @param elemento el elemento a eliminar.
     * @throws NoSuchElementException si el elemento no está
     *         contenido en la gráfica.
     */
    public void elimina(T elemento) {
	if(!(vertices.contiene(elemento)))
	    throw new NoSuchElementException();
	else{
	    Vertice<T> vertice = vertices.get(elemento);        
	    for(Arista<T> ar : vertice.aristas){
		desconecta(elemento, ar.vecino.elemento);
	    }
	    vertices.elimina(elemento);
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
	if(!(vertices.contiene(a) && vertices.contiene(b)))
	    throw new NoSuchElementException();
	Vertice<T> verticeA = vertices.get(a);
	Vertice<T> verticeB = vertices.get(b);
	return verticeA.aristas.contiene(b);
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
	if(!(vertices.contiene(a) && vertices.contiene(b)))
	    throw new NoSuchElementException();
	Vertice<T> verticeA = vertices.get(a);
	Vertice<T> verticeB = vertices.get(b);
	if(verticeA.aristas.contiene(b))
	    return verticeA.aristas.get(b).peso;
	return -1; 
    }

    /**
     * Regresa el vértice correspondiente el elemento recibido.
     * @throws NoSuchElementException si elemento no es elemento de
     *         la gráfica.
     * @return el vértice correspondiente el elemento recibido.
     */
    public VerticeGrafica<T> vertice(T elemento) {
	if(vertices.contiene(elemento))
	    return vertices.get(elemento);
	throw new NoSuchElementException();
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
	if(!vertices.contiene(elemento))
	    throw new NoSuchElementException();
	else{
	    Vertice<T> raiz = vertices.get(elemento);       
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
		    for(int i = 0; i < vertices.getTotal(); i++){
			for(Vertice<T> v : vertices){
			    temp = v;
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
	if(!vertices.contiene(elemento))
	    throw new NoSuchElementException();
	else{
	    Vertice<T> raiz = vertices.get(elemento);       
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
		    for(int i = 0; i < vertices.getTotal(); i++){
			for(Vertice<T> v : vertices){
			    temp = v;
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
	    }
	    for(Vertice<T> ver : vertices){
		ver.setColor(Color.NINGUNO);
	    }
	}
    }

    /**
     * Regresa un iterador para iterar la gráfica. La gráfica se
     * itera en el orden en que fueron agregados sus elementos.
     * @return un iterador para iterar la gráfica.
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
	if(!(vertices.contiene(origen) && vertices.contiene(destino)))
	    throw new NoSuchElementException();
	else{
	    Vertice<T> verticeA = vertices.get(origen);
	    Vertice<T> verticeB = vertices.get(destino);	    
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
	    verTemp = temp.vertices.get(origen);
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
	if(!(vertices.contiene(origen) && vertices.contiene(destino)))
	    throw new NoSuchElementException();
	else{
	    Vertice<T> verticeA = vertices.get(origen);
	    Vertice<T> verticeB = vertices.get(destino);	    
	    Vertice<T> verTemp = verticeA;
	    MonticuloMinimo<Grafica<T>.Vertice<T>> monticulo = new MonticuloMinimo<Grafica<T>.Vertice<T>>();	    
	    verTemp.distancia = 0;
	    monticulo.agrega(verTemp);
	    verTemp.setColor(Color.ROJO);
	    while(!monticulo.esVacio()){
		verTemp = monticulo.elimina();
		for(Arista<T> ari : verTemp.aristas){
		    if((verTemp.distancia+ari.peso < ari.vecino.distancia
			|| ari.vecino.distancia == -1)){
			ari.vecino.distancia = (verTemp.distancia+ari.peso);
			monticulo.agrega(ari.vecino);
			ari.vecino.setColor(Color.ROJO);
		    }
		}
	    }
	    if(verticeB.getColor() != Color.ROJO)
		return ret;
	    verTemp = temp.vertices.get(origen);
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
	for(Grafica<T>.Vertice<T> ver : temp.vertices){
	    ver.distancia =-1;
	    ver.setColor(Color.NINGUNO);
	}
	return ret; 
    }
    
    /**
     * Metodo para representar en una imagen SVG una grafica.
     * @return - Nos regresa la imagen SVG en forma de cadena.
     */
    public String generaScalableVectorGraphics() {
	//Para evitar problemas de una arista encima de un vértice haré la gráfica de forma circular.
	double radioC, radio, alto, anguloInic, anguloTemp;
	radioC = 20;
	radio = radio(radioC);
	alto = (2*radio)+(4*radioC);
	//Para que sea vea más bonito hago 2 casos y uso 2 diccionarios.
	Diccionario<Grafica<T>.Vertice<T>,Lista<Double>> posicion = 
	    new Diccionario<Grafica<T>.Vertice<T>,Lista<Double>>(getVertices());
	Diccionario<Grafica<T>.Vertice<T>,Lista<Double>> dAristas = 
	    new Diccionario<Grafica<T>.Vertice<T>,Lista<Double>>(getVertices());
	anguloInic = ((2*Math.PI)/getVertices());
	anguloTemp = anguloInic;
	for(Grafica<T>.Vertice<T> ver : vertices){
	    Lista<Double> pos = new Lista<Double>();
	    Lista<Double> posAri = new Lista<Double>();
	    pos.agregaInicio(posX(radio, anguloTemp)+alto/2);
	    pos.agregaFinal(posY(radio, anguloTemp)+alto/2);
	    posAri.agregaInicio(posX(radio-radioC, anguloTemp)+alto/2);
	    posAri.agregaFinal(posY(radio-radioC, anguloTemp)+alto/2);
	    posicion.agrega(ver, pos);
	    dAristas.agrega(ver, posAri);
	    anguloTemp += anguloInic;
	}
	String grafica = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
	    +"<svg width=\""+alto+"\" height=\""+alto+"\">\n"
	    +"<g>\n";
	//Después de 13 vértices en la gráfica completa las aristas enciman vértices si no hago esto:
	if(getVertices() > 13)
	    grafica = grafica.concat(generaAristas(dAristas, radioC));
	else
	    grafica = grafica.concat(generaAristas(posicion, radioC));
	grafica = grafica.concat(generaCirculos(posicion, radioC));
	grafica = grafica.concat(generaElementos(posicion, radioC));
	grafica = grafica.concat("</g> \n </svg>");
	return grafica;
    }

    /**
     * Metodo para representar en una imagen SVG una grafica.
     * @param lista - Es la lista que nos dan para sobresaltar la trayectoria.
     * @return - Nos regresa la imagen SVG en forma de cadena.
     */
    public String generaScalableVectorGraphics(Lista<VerticeGrafica<T>> lista) {
	//Para evitar problemas de una arista encima de un vértice haré la gráfica de forma circular.
	double radioC, radio, alto, anguloInic, anguloTemp;
	radioC = 20;
	radio = radio(radioC);
	alto = (2*radio)+(4*radioC);
	//Para que sea vea más bonito hago 2 casos y uso 2 diccionarios.
	Diccionario<Grafica<T>.Vertice<T>,Lista<Double>> posicion = 
	    new Diccionario<Grafica<T>.Vertice<T>,Lista<Double>>(getVertices());
	Diccionario<Grafica<T>.Vertice<T>,Lista<Double>> dAristas = 
	    new Diccionario<Grafica<T>.Vertice<T>,Lista<Double>>(getVertices());
	anguloInic = ((2*Math.PI)/getVertices());
	anguloTemp = anguloInic;
	for(Grafica<T>.Vertice<T> ver : vertices){
	    Lista<Double> pos = new Lista<Double>();
	    Lista<Double> posAri = new Lista<Double>();
	    pos.agregaInicio(posX(radio, anguloTemp)+alto/2);
	    pos.agregaFinal(posY(radio, anguloTemp)+alto/2);
	    posAri.agregaInicio(posX(radio-radioC, anguloTemp)+alto/2);
	    posAri.agregaFinal(posY(radio-radioC, anguloTemp)+alto/2);
	    posicion.agrega(ver, pos);
	    dAristas.agrega(ver, posAri);
	    anguloTemp += anguloInic;
	}
	String grafica = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
	    +"<svg width=\""+alto+"\" height=\""+alto+"\">\n"
	    +"<g>\n";
	//Después de 13 vértices en la gráfica completa las aristas enciman vértices si no hago esto:
	if(getVertices() > 13)
	    grafica = grafica.concat(generaAristas(dAristas, radioC, lista));
	else
	    grafica = grafica.concat(generaAristas(posicion, radioC, lista));
	grafica = grafica.concat(generaCirculos(posicion, radioC));
	grafica = grafica.concat(generaElementos(posicion, radioC));
	grafica = grafica.concat("</g> \n </svg>");
	return grafica;
    }
    
    //Método privado que nos da el radio de mi gráfica.
    private double radio(double radioC){
	return (2*getVertices()*(2*radioC))/(Math.PI*2);
    }
    
    //Métpdp privado que nos da la posición X de cada vértice.
    private double posX(double radio, double angulo){
	return (radio*(Math.cos(angulo)));
    }
    
    //Método privado que nos da la posición Y de cada vértice.
    private double posY(double radio, double angulo){
	return (radio*(Math.sin(angulo)));
    }

    //Método privado para generar el código SVG de los vértices.
    private String generaCirculos(Diccionario<Grafica<T>.Vertice<T>,Lista<Double>> posicion,
				  double radioC){
	String fin = "";
	String color = "white";
	double anguloInic = ((2*Math.PI)/getVertices());
	double angulo = anguloInic;
	for(Grafica<T>.Vertice<T> ver : vertices){
	    fin = fin.concat("<circle cx=\""+(posicion.get(ver).getPrimero())
			     +"\" cy=\""+(posicion.get(ver).getUltimo())+"\""
			     +" r=\""+(radioC)+"\" stroke=\"black\" stroke-width=\"3\" fill =\""+(color)+"\" />\n");	    
	}
	return fin;
    }
    
    //Método privado que nos genera el código SVG de las aristas.
    private String generaAristas(Diccionario<Grafica<T>.Vertice<T>,Lista<Double>> posicion,
				 double radioC){
	String fin= "";
	int i = 0;
	String color = null;
	String[] colores = coloresSVG();
	Diccionario<Grafica<T>.Vertice<T>, Integer> dicc = 
	    new Diccionario<Grafica<T>.Vertice<T>, Integer>(getVertices());
	for(Grafica<T>.Vertice<T> ver : vertices){
	    for(Arista<T> ari : ver.aristas){
		if(!dicc.contiene(ari.vecino)){
		    double x1, x2, y1, y2;
		    x1 = posicion.get(ver).getPrimero();
		    x2 = posicion.get(ari.vecino).getPrimero();
		    y1 = posicion.get(ver).getUltimo();
		    y2 = posicion.get(ari.vecino).getUltimo();
		    color = colores[i%colores.length];
		    i++;
		    fin = fin.concat("<line x1=\""+(x1)+
				     "\" y1=\""+(y1)+"\" x2=\""+(x2)+
				     "\" y2=\""+(y2)+"\" stroke=\""+(color)+"\" stroke-width=\"1.5\" />\n");
		}
	    }
	    dicc.agrega(ver, 1);
	}
	return fin;
    }

    //Método privado que nos genera el código SVG de las aristas y resalta la indicada.
    private String generaAristas(Diccionario<Grafica<T>.Vertice<T>,Lista<Double>> posicion,
				 double radioC, Lista<VerticeGrafica<T>> lista){
	String fin= "";
	String[] colores = coloresSVG();
	String color = colores[0];
	Diccionario<Grafica<T>.Vertice<T>, Integer> dicc = 
	    new Diccionario<Grafica<T>.Vertice<T>, Integer>(getVertices());
	for(Grafica<T>.Vertice<T> ver : vertices){
	    for(Arista<T> ari : ver.aristas){
		if(!dicc.contiene(ari.vecino)){
		    double x1, x2, y1, y2;
		    x1 = posicion.get(ver).getPrimero();
		    x2 = posicion.get(ari.vecino).getPrimero();
		    y1 = posicion.get(ver).getUltimo();
		    y2 = posicion.get(ari.vecino).getUltimo();		    
		    fin = fin.concat("<line x1=\""+(x1)+
				     "\" y1=\""+(y1)+"\" x2=\""+(x2)+
				     "\" y2=\""+(y2)+"\" stroke=\""+(color)+"\" stroke-width=\"1.5\" />\n");
		}
	    }
	    dicc.agrega(ver, 1);		    
	}
		    VerticeGrafica<T> tem = lista.eliminaPrimero();
		    color = colores[4];
		    while(lista.getLongitud() > 0){
		    VerticeGrafica<T> temp = lista.eliminaPrimero();
		    fin = fin.concat("<line x1=\""+(posicion.get(vertices.get(tem.getElemento())).getPrimero())+
				     "\" y1=\""+(posicion.get(vertices.get(tem.getElemento())).getUltimo())
				     +"\" x2=\""+(posicion.get(vertices.get(temp.getElemento())).getPrimero())+
				     "\" y2=\""+(posicion.get(vertices.get(temp.getElemento())).getUltimo())+
				     "\" stroke=\""+(color)+"\" stroke-width=\"1.5\" />\n");		  
		    tem = temp;
	}
	return fin;
    }
    
    //Método privado que nos genera código SVG de los elementos de los vértices.
    private String generaElementos(Diccionario<Grafica<T>.Vertice<T>,Lista<Double>> posicion,
				 double radioC){
	String fin = "";
	String colorTexto = "black";
	for(Grafica<T>.Vertice<T> ver : vertices){
	    double x1, y1;
	    x1 = posicion.get(ver).getPrimero();
	    y1 = posicion.get(ver).getUltimo();	    
	    fin = fin.concat("<text fill=\""+(colorTexto)+"\""
			     +" font-family=\"sens-serif\" font-size=\"15\""
			     +" x=\""+(x1)+"\" y=\""+(y1+5)+"\""
			     +" text-anchor=\"middle\">"+ver.elemento+"</text>\n");
	}
	return fin;
    }

    //Método privado que nos regresa un arreglo con los posibles colores de las aristas.
    private static String[] coloresSVG(){
	String[] colores = {"black","purple","blue","green","red","yellow","violet","blueviolet","orange",
			    "magenta","darkred","black","brown","burlywood","cadetblue","chartreuse","chocolate",
			    "cornflowerblue","crimson","black","cyan","darkblue","darkcyan","darkgoldenrod","aqua",
			    "darkgray","darkgreen","darkkhaki","black","darkmagenta","darkolivegreen","darkorange",
			    "darkorchid","darksalmon","darkseagreen","black","antiquewhite","darkslateblue","coral",
			    "darkslategrey","darkturquoise","darkviolet","black","deeppink","deepskyblue","firebrick",
			    "forestgreen","fuchsia","gold","gray","greenyellow","black","hotpink","indianred","indigo",
			    "aquamarine","lawngreen","lightblue","lightseagreen","lime","black","maroon","mediumblue",
			    "navy","olive","olivedrab","orangered","orchid","peru","black","pink","plum","powderblue",
			    "rosybrown","royalblue","saddlebrown","salmon","sandybrown","black","seagreen","sienna",
			    "skyblue","slateblue","slategrey","springgreen","steelblue","teal","black","tan","tomato",
			    "turquoise","yellowgreen"};
	return colores;
    }

} //Fin de Grafica.java