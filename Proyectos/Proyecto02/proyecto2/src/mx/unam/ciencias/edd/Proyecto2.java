package mx.unam.ciencias.edd;

import java.util.Random;

/**
 * Proyecto 2: SVG graficas.
 */
public class Proyecto2 {

public static void mje(){
	System.out.println("Para ver ejemplos debe escribir \"java -jar proyecto2.jar [*] \n"+
		   "[*] es el caso = \"cadenas\", \"enteros\", \"dobles\" (Sin comillas)");
}

    public static void main(String[] args) {
	String[] cadena = { "a" , "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",	
			    "n","ñ","o","p","q","r","s","t","u","v","w","x","y","z", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",	
			    "n","ñ","o","p","q","r","s","t","u","v","w","x","y","z", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",	
			    "n","ñ","o","p","q","r","s","t","u","v","w","x","y","z", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",	
			    "n","ñ","o","p","q","r","s","t","u","v",};
double[] arbol0 = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,57,56,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100};

	double[] arbol1 = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,57,56,58,59,60,62};
	int[] enteros0 = {0};
	int[] enteros1 = {0, 1};
	int[] enteros2 = {0, 1, 2};
	int[] enteros3 = {0, 1, 2, 3,};
	int[] enteros4 = {0, 1, 2, 3, 4, 5, 6,};
	int[] enteros5 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int[] enteros6 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	int[] enteros7 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
	int[] enteros8 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,14,15,16,17};
	int[] enteros9 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,14,15,16,17,18,19,20};
	if(args.length == 1){	
	if(args[0].equalsIgnoreCase("cadenas")){	
	Grafica<String> g = new Grafica<String>();
        g.agrega("a");
        g.agrega("b");
        g.agrega("c");
        g.agrega("d");
        g.agrega("e");
        g.agrega("f");

        g.conecta("a", "b");
        g.conecta("a", "c");
        g.conecta("b", "c");
        g.conecta("b", "d");
        g.conecta("b", "e");
        g.conecta("c", "e");
        g.conecta("d", "e");
        g.conecta("d", "f");
        g.conecta("e", "f");
	System.out.println(g.generaScalableVectorGraphics());	
	}else if(args[0].equalsIgnoreCase("dobles1")){
	Grafica<Double> l = new Grafica<Double>();
        for (int i = 0; i < arbol1.length; i++){	
l.agrega(arbol1[i]);
	}
	//ARISTAS
	for(int j = 0; j < arbol1.length; j++){
	for(int h = j; h < arbol1.length; h++){
		if(!(h == j || l.sonVecinos(arbol1[j], arbol1[h])))
		l.conecta(arbol1[j], arbol1[h]);
		}
j += 3; 
	}
	//TERMINA ARISTAS
	System.out.println(l.generaScalableVectorGraphics());	
}else if(args[0].equalsIgnoreCase("dobles0")){
	Grafica<Double> l = new Grafica<Double>();
        for (int i = 0; i < arbol0.length; i++){	
l.agrega(arbol0[i]);
	}
	//ARISTAS/*
	for(int j = 0; j < arbol0.length; j++){
	for(int h = j; h < arbol0.length; h++){
		if(!(h == j || l.sonVecinos(arbol0[j], arbol0[h])))
		l.conecta(arbol0[j], arbol0[h]);
		}
j += 3; 
	}
	//TERMINA ARISTAS*/
	System.out.println(l.generaScalableVectorGraphics());	
	}else if(args[0].equalsIgnoreCase("enteros0")){
	Grafica<Integer> l = new Grafica<Integer>();
        for (int i = 0; i < enteros0.length; i++){
		l.agrega(enteros0[i%enteros0.length]);
	}
	//ARISTAS
	for(int j = 0; j < enteros0.length; j++){
	for(int h =0; h < enteros0.length; h++){
		if(!(h == j || l.sonVecinos(enteros0[j], enteros0[h])))
		l.conecta(enteros0[j], enteros0[h]);} 
	}
	//TERMINA ARISTAS
	System.out.println(l.generaScalableVectorGraphics());	
    	}else if(args[0].equalsIgnoreCase("enteros1")){
	Grafica<Integer> l = new Grafica<Integer>();
        for (int i = 0; i < enteros1.length; i++){
		l.agrega(enteros1[i%enteros1.length]);
	}
	//ARISTAS
	for(int j = 0; j < enteros1.length; j++){
	for(int h =0; h < enteros1.length; h++){
		if(!(h == j || l.sonVecinos(enteros1[j], enteros1[h])))
		l.conecta(enteros1[j], enteros1[h]);} 
	}
	//TERMINA ARISTAS
	System.out.println(l.generaScalableVectorGraphics());	
	}else if(args[0].equalsIgnoreCase("enteros2")){
	Grafica<Integer> l = new Grafica<Integer>();
        for (int i = 0; i < enteros2.length; i++){
		l.agrega(enteros2[i%enteros2.length]);
	}
	//ARISTAS
	for(int j = 0; j < enteros2.length; j++){
	for(int h =0; h < enteros2.length; h++){
		if(!(h == j || l.sonVecinos(enteros2[j], enteros2[h])))
		l.conecta(enteros2[j], enteros2[h]);} 
	}
	//TERMINA ARISTAS
	System.out.println(l.generaScalableVectorGraphics());	
}else if(args[0].equalsIgnoreCase("enteros3")){
	Grafica<Integer> l = new Grafica<Integer>();
        for (int i = 0; i < enteros3.length; i++){
		l.agrega(enteros3[i%enteros3.length]);
	}
	//ARISTAS
	for(int j = 0; j < enteros3.length; j++){
	for(int h =0; h < enteros3.length; h++){
		if(!(h == j || l.sonVecinos(enteros3[j], enteros3[h])))
		l.conecta(enteros3[j], enteros3[h]);} 
	}
	//TERMINA ARISTAS
	System.out.println(l.generaScalableVectorGraphics());	
}else if(args[0].equalsIgnoreCase("enteros4")){
	Grafica<Integer> l = new Grafica<Integer>();
        for (int i = 0; i < enteros4.length; i++){
		l.agrega(enteros4[i%enteros4.length]);
	}
	//ARISTAS
	for(int j = 0; j < enteros4.length; j++){
	for(int h =0; h < enteros4.length; h++){
		if(!(h == j || l.sonVecinos(enteros4[j], enteros4[h])))
		l.conecta(enteros4[j], enteros4[h]);} 
	}
	//TERMINA ARISTAS
	System.out.println(l.generaScalableVectorGraphics());	
}else if(args[0].equalsIgnoreCase("enteros5")){
	Grafica<Integer> l = new Grafica<Integer>();
        for (int i = 0; i < enteros5.length; i++){
		l.agrega(enteros5[i%enteros5.length]);
	}
	//ARISTAS
	for(int j = 0; j < enteros5.length; j++){
	for(int h =0; h < enteros5.length; h++){
		if(!(h == j || l.sonVecinos(enteros5[j], enteros5[h])))
		l.conecta(enteros5[j], enteros5[h]);} 
	}
	//TERMINA ARISTAS
	System.out.println(l.generaScalableVectorGraphics());	
}else if(args[0].equalsIgnoreCase("enteros6")){
	Grafica<Integer> l = new Grafica<Integer>();
        for (int i = 0; i < enteros6.length; i++){
		l.agrega(enteros6[i%enteros6.length]);
	}
	//ARISTAS
	for(int j = 0; j < enteros6.length; j++){
	for(int h =0; h < enteros6.length; h++){
		if(!(h == j || l.sonVecinos(enteros6[j], enteros6[h])))
		l.conecta(enteros6[j], enteros6[h]);} 
	}
	//TERMINA ARISTAS
	System.out.println(l.generaScalableVectorGraphics());	
}else if(args[0].equalsIgnoreCase("enteros7")){
	Grafica<Integer> l = new Grafica<Integer>();
        for (int i = 0; i < enteros7.length; i++){
		l.agrega(enteros7[i%enteros7.length]);
	}
	//ARISTAS
	for(int j = 0; j < enteros7.length; j++){
	for(int h =0; h < enteros7.length; h++){
		if(!(h == j || l.sonVecinos(enteros7[j], enteros7[h])))
		l.conecta(enteros7[j], enteros7[h]);} 
	}
	//TERMINA ARISTAS
	System.out.println(l.generaScalableVectorGraphics());	
}else if(args[0].equalsIgnoreCase("enteros8")){
	Grafica<Integer> l = new Grafica<Integer>();
        for (int i = 0; i < enteros8.length; i++){
		l.agrega(enteros8[i%enteros8.length]);
	}
	//ARISTAS
	for(int j = 0; j < enteros8.length; j++){
	for(int h =0; h < enteros8.length; h++){
		if(!(h == j || l.sonVecinos(enteros8[j], enteros8[h])))
		l.conecta(enteros8[j], enteros8[h]);} 
	}
	//TERMINA ARISTAS
	System.out.println(l.generaScalableVectorGraphics());	
}else if(args[0].equalsIgnoreCase("enteros9")){
	Grafica<Integer> l = new Grafica<Integer>();
        for (int i = 0; i < enteros9.length; i++){
		l.agrega(enteros9[i%enteros9.length]);
	}
	//ARISTAS
	for(int j = 0; j < enteros9.length; j++){
	for(int h =0; h < enteros9.length; h++){
		if(!(h == j || l.sonVecinos(enteros9[j], enteros9[h])))
		l.conecta(enteros9[j], enteros9[h]);} 
	}
	//TERMINA ARISTAS
	System.out.println(l.generaScalableVectorGraphics());	
}else if(args[0].equalsIgnoreCase("enteroslista")){
	Grafica<Integer> l = new Grafica<Integer>();
        for (int i = 0; i < enteros6.length; i++){
		l.agrega(enteros6[i%enteros6.length]);
	}
	Lista<VerticeGrafica<Integer>> lista = new Lista<VerticeGrafica<Integer>>();
	lista.agregaFinal(l.vertice(enteros9[0]));
	lista.agregaFinal(l.vertice(enteros9[1]));
	lista.agregaFinal(l.vertice(enteros9[2]));
	lista.agregaFinal(l.vertice(enteros9[6]));
	lista.agregaFinal(l.vertice(enteros9[5]));
	lista.agregaFinal(l.vertice(enteros9[1]));
	lista.agregaFinal(l.vertice(enteros9[10]));
	lista.agregaFinal(l.vertice(enteros9[2]));
	lista.agregaFinal(l.vertice(enteros9[11]));
	//ARISTAS
	for(int j = 0; j < enteros6.length; j++){
	for(int h =0; h < enteros6.length; h++){
		if(!(h == j || l.sonVecinos(enteros6[j], enteros6[h])))
		l.conecta(enteros6[j], enteros6[h]);} 
	}
	//TERMINA ARISTAS
	System.out.println(l.generaScalableVectorGraphics(lista));	

	}else{
 	mje();	
	}
}else{	
mje();
}
    }
}
