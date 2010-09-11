/**
 * Equação Diferencial Ordinária
 * @author Rafael de Castro Dantas Sales - rafaelcds@gmail.com
 */
public interface EDO {
	/**
	 * dx/dt = f(x, t).
	 * f(x, t) é dada.
	 * A incógnita é a função x(t).
	 * t pertence a um intervalo ou a reta real inteira.
	 * @param x
	 * @param t
	 * @param i
	 * @return
	 */
	double calcular(double x, double t, int i);
}
