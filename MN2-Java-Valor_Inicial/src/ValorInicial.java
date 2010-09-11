/**
 * Implementação dos métodos de Valor Inicial
 * @author Rafael de Castro Dantas Sales - rafaelcds@gmail.com
 */
public class ValorInicial {
	
	private ValorInicial() {
	}
	
	/**
	 * Executa o método Forward Euler para estimar pontos
	 * @param edo - Equação Diferencial Ordinária
	 * @param valorInicial Valor inicial a ser utilizado na EDO
	 * @param intervaloA Limite inferior do intervalo
	 * @param intervaloB Limite superior do intervalo
	 * @param discretizacao
	 * @return matriz onde a primeira linha contém os valores da abscissa e 
	 * a segunda linha contém os respectivos valores da ordenada 
	 */
	public static double[][] forwardEuler(EDO edo, double valorInicial, double intervaloA, double intervaloB, double discretizacao) {
		int numPontos = (int) Math.ceil((intervaloB - intervaloA) / discretizacao) + 1;
		double[][] pontos = new double[2][numPontos];
		double novo = valorInicial;
		int i;
		double t;
		for (i = 0, t = intervaloA; i < numPontos; i++, t += discretizacao) {
			pontos[0][i] = t;
			pontos[1][i] = novo;
			novo = novo + discretizacao * edo.calcular(novo, t, i);
		}
		return pontos;
	}
	
	/**
	 * Executa o método Backward Euler para estimar pontos
	 * @param funcaoProximoPonto função que estima o próximo ponto
	 * @param valorInicial Valor inicial a ser utilizado na EDO
	 * @param intervaloA Limite inferior do intervalo
	 * @param intervaloB Limite superior do intervalo
	 * @param discretizacao
	 * @return matriz onde a primeira linha contém os valores da abscissa e 
	 * a segunda linha contém os respectivos valores da ordenada 
	 */
	public static double[][] backwardEuler(final EDO funcaoProximoPonto, double valorInicial, double intervaloA, double intervaloB, double discretizacao) {
		int numPontos = (int) Math.ceil((intervaloB - intervaloA) / discretizacao) + 1;
		double[][] pontos = new double[2][numPontos];
		double novo = valorInicial;
		int i;
		double t;
		for (i = 0, t = intervaloA; i < numPontos; i++, t += discretizacao) {
			pontos[0][i] = t;
			pontos[1][i] = novo;
			novo = funcaoProximoPonto.calcular(novo, t, i);
		}
		return pontos;
	}
	
	/**
	 * Executa o método Runge-Kutta de Terceira Ordem para estimar pontos
	 * @param edo - Equação Diferencial Ordinária
	 * @param valorInicial Valor inicial a ser utilizado na EDO
	 * @param intervaloA Limite inferior do intervalo
	 * @param intervaloB Limite superior do intervalo
	 * @param discretizacao
	 * @return
	 */
	public static double[][] rungeKuttaTerceiraOrdem(EDO edo, double valorInicial, double intervaloA, double intervaloB, double discretizacao) {
		int numPontos = (int) Math.ceil((intervaloB - intervaloA) / discretizacao) + 1;
		double[][] pontos = new double[2][numPontos];
		double novo = valorInicial;
		int i;
		double t;
		double h = discretizacao;
		for (i = 0, t = intervaloA; i < numPontos; i++, t += discretizacao) {
			pontos[0][i] = t;
			pontos[1][i] = novo;
			double k1 = h * edo.calcular(novo, t, i);
			double k2 = h * edo.calcular(novo + 0.5 * k1, t + h / 2, i);
			double k3 = h * edo.calcular(novo - k1 + 2 * k2, t + h, i);
			novo = novo + (k1 + 4 * k2 + k3) / 6;
		}
		return pontos;
	}
	
	/**
	 * Executa o método Preditor-Corretor de Terceira Ordem para estimar pontos
	 * @param edo - Equação Diferencial Ordinária
	 * @param inicializacao 3 valores iniciais
	 * @param intervaloA Limite inferior do intervalo
	 * @param intervaloB Limite superior do intervalo
	 * @param discretizacao
	 * @return
	 */
	public static double[][] preditorCorretorTerceiraOrdem(EDO edo, double[][] inicializacao, double intervaloA, double intervaloB, double discretizacao) {
		int numPontos = (int) Math.ceil((intervaloB - intervaloA) / discretizacao) + 1;
		double[][] pontos = new double[2][numPontos];
		int i;
		double t;
		pontos[0][0] = inicializacao[0][0];
		pontos[1][0] = inicializacao[1][0];
		pontos[0][1] = inicializacao[0][1];
		pontos[1][1] = inicializacao[1][1];
		double novo = inicializacao[1][2];
		for (i = 2, t = intervaloA + 2 * discretizacao; i < numPontos - 1; i++, t += discretizacao) {
			//Preditor:
			pontos[0][i] = t;
			pontos[1][i] = novo;
			
			//Fórumla preditora de terceira ordem de Adams-Bashforth
			double edoI1 = edo.calcular(pontos[1][i], t, i);
			double edoI2 = edo.calcular(pontos[1][i - 1], t - discretizacao, i - 1);
			double edoI3 = edo.calcular(pontos[1][i - 2], t - 2 * discretizacao, i - 2);
			novo = pontos[1][i] + discretizacao * (23 * edoI1 - 16 * edoI2 + 5 * edoI3) / 12;
			pontos[0][i + 1] = t + discretizacao;
			pontos[1][i + 1] = novo;
			
			//Fórmula corretora de terceira ordem de Adams-Moulton
			edoI1 = edo.calcular(pontos[1][i + 1], t + discretizacao, i + 1);
			edoI2 = edo.calcular(pontos[1][i], t, i);
			edoI3 = edo.calcular(pontos[1][i - 1], t - discretizacao, i - 1);
			novo = pontos[1][i] + discretizacao * (5 * edoI1 + 8 * edoI2 - edoI3) / 12;
			pontos[1][i + 1] = novo;
		}
		return pontos;
	}
}