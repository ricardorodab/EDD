/* -------------------------------------------------------------------
 * FabricaHuellasDigitales.java
 * versión 1.5
 * Copyright (C) 2014  José Ricardo Rodríguez Abreu.
 * Facultad de Ciencias,
 * Universidad Nacional Autónoma de México, Mexico.
 *
 * Este programa es software libre; se puede redistribuir
 * y/o modificar en los términos establecidos por la
 * Licencia Pública General de GNU tal como fue publicada
 * por la Free Software Foundation en la versión 2 o
 * superior.
 *
 * Este programa es distribuido con la esperanza de que
 * resulte de utilidad, pero SIN GARANTÍA ALGUNA; de hecho
 * sin la garantía implícita de COMERCIALIZACIÓN o
 * ADECUACIÓN PARA PROPÓSITOS PARTICULARES. Véase la
 * Licencia Pública General de GNU para mayores detalles.
 *
 * Con este programa se debe haber recibido una copia de la
 * Licencia Pública General de GNU, de no ser así, visite el
 * siguiente URL:
 * http://www.gnu.org/licenses/gpl.html
 * o escriba a la Free Software Foundation Inc.,
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * -------------------------------------------------------------------
 */
package mx.unam.ciencias.edd;

/**
 * @autor Jose Ricardo Rodriguez Abreu.
 * @version 1.5
 * @since May 6, 2014.
 * Clase para fabricar generadores de huellas digitales.
 */
public class FabricaHuellasDigitales {
    
    /**
     * Identificador para fabricar la huella digital de Bob
     * Jenkins para cadenas.
     */
    public static final int BJ_STRING   = 0;
    /**
     * Identificador para fabricar la huella digital de GLib para
     * cadenas.
     */
    public static final int GLIB_STRING = 1;
    /**
     * Identificador para fabricar la huella digital de XOR para
     * cadenas.
     */
    public static final int XOR_STRING  = 2;
    
    /**
     * Regresa una instancia de {@link HuellaDigital} para cadenas.
     * @param identificador el identificador del tipo de huella
     *        digital que se desea.
     * @throws IllegalArgumentException si recibe un identificador
     *         no reconocido.
     */
    public static HuellaDigital<String> getInstanciaString(int identificador) {
	if(identificador == 0){
	    return new HuellaDigital<String>(){
		@Override
		    public int huellaDigital(String pal){
		    byte[] letras = pal.getBytes();
		    int a, b, c, l, i;
		    l = letras.length;
		    a = b = 0x9e3779b9;
		    c = 0xffffffff;
		    i = 0;
		    while(l >= 12){
			a+= (letras[i+0] + (letras[i+1] << 8) + (letras[i+2] << 16) + (letras[i+3] << 24));
			b+= (letras[i+4] + (letras[i+5] << 8) + (letras[i+6] << 16) + (letras[i+7] << 24));
			c+= (letras[i+8] + (letras[i+9] << 8) + (letras[i+10] << 16) + (letras[i+11] << 24));			
			a-=b; a-=c; a^=(c>>>13);	
			b-=c; b-=a; b^=(a<<8);
			c-=a; c-=b; c^=(b>>>13);
			a-=b; a-=c; a^=(c>>>12);
			b-=c; b-=a; b^=(a<<16);
			c-=a; c-=b; c^=(b>>>5);
			a-=b; a-=c; a^=(c>>>3);
			b-=c; b-=a; b^=(a<<10);
			c-=a; c-=b; c^=(b>>>15);
			i+= 12;
			l-= 12;
		    }
		    c += letras.length;
		    switch(l){
		    case 11: c+= (letras[i+10] << 24);
		    case 10: c+= (letras[i+9] << 16);
		    case 9: c+= (letras[i+8] << 8);
		    case 8: b+= (letras[i+7] << 24);
		    case 7: b+= (letras[i+6] << 16);
		    case 6: b+= (letras[i+5] << 8);
		    case 5: b+= (letras[i+4]);
		    case 4: a+= (letras[i+3] << 24);
		    case 3: a+= (letras[i+2] << 16);
		    case 2: a+= (letras[i+1] << 8);
		    case 1: a+= (letras[i+0]);
		    }
		    a-=b; a-=c; a^=(c>>>13);	
		    b-=c; b-=a; b^=(a<<8);
		    c-=a; c-=b; c^=(b>>>13);
		    a-=b; a-=c; a^=(c>>>12);
		    b-=c; b-=a; b^=(a<<16);
		    c-=a; c-=b; c^=(b>>>5);
		    a-=b; a-=c; a^=(c>>>3);
		    b-=c; b-=a; b^=(a<<10);
		    c-=a; c-=b; c^=(b>>>15);		    		    
		    return c;
		}
	    }; 
	}else if(identificador == 1){
	    return new HuellaDigital<String>(){
		@Override
		    public int huellaDigital(String pal){
		    byte[] letras = pal.getBytes();
		    int h = 5381;
		    for(int i = 0; i< letras.length; i++){
			char c = (char)letras[i];
			h = h*33+ c;
		    }
		    return h;
		}
	    };     
	}else if(identificador == 2){
	    return new HuellaDigital<String>(){
		@Override
		    public int huellaDigital(String pal){
		    byte[] letras = pal.getBytes();
		    int i = letras.length;
		    int c = 0;		    		  
		    while(i >= 0){
			byte a, b, b2, d;
			a = b = b2 = d =0;
			if(i < 4){
			    if(i == 3){
				b = letras[i-3];
				b2 = letras[i-2];
				d = letras[i-1];
			    }else if(i == 2){		
				b2 = letras[i-2];
				d = letras[i-1];		
			    }else if(i == 1){
				d = letras[i-1];
			    }
			}else{
			    a = letras[i-4];
			    b = letras[i-3];
			    b2 = letras[i-2];
			    d = letras[i-1];
			}
			c ^= (a<<24) | (b<<16) | (b2<<8) | d;
			i-=4;
		    }
		    return c;
		}
	    };
	}else{
	    throw new IllegalArgumentException();
	}
    }
}//Fin de FabricaHuellasDigitales.java