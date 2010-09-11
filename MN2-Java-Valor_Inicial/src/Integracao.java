/**
 * Métodos de integração
 * @author Rafael de Castro Dantas Sales - rafaelcds@gmail.com
 */
public class Integracao {
	private Integracao() {
	}
	
	public static double calcularGaussLegendre(Funcao funcao, double intervaloA, double intervaloB, int numPontos) {
		if (numPontos < 2 || numPontos > 4) {
			throw new RuntimeException("Número de pontos inválido. Valores possíveis: 2, 3 e 4");
		}
		/* Tabelas com os pontos de Legendre.
		 * A primeira coluna é o ponto de Legendre e a segunda é o peso correspondente.
		 */
		double[][] tabelaLegendreN2 = new double[][] {
				{ -0.577350269, 1.0 },
				{ 0.577350269, 1.0 }
		};
		double[][] tabelaLegendreN3 = new double[][] {
				{ -0.774596669, 0.555555556 },
				{ 0, 0.888888889 },
				{ 0.774596669, 0.555555556 }
		};
		double[][] tabelaLegendreN4 = new double[][] {
				{ -0.861136312, 0.347854845 },
				{ -0.339981043, 0.652145155 },
				{ 0.339981043, 0.652145155 },
				{ 0.861136312, 0.347854845 }
		};
		
		double resultadoAtual = 0.0;
		double tamanhoIntervalo;
		
		resultadoAtual = 0.0;
		tamanhoIntervalo = (intervaloB - intervaloA);
		//I = [(b - a) / 2] * [Somatorio dos pesos multiplicados pelos f((pl * (b - a) + a + b) / 2)] onde pl é um ponto de Legendre
		double resultadoSubintervalo = 0.0;
		for (int iPL = 0; iPL < numPontos; iPL++) {
			double pl = 0.0; //Ponto de Legendre atual
			double peso = 0.0; //Peso correspondente ao peso de Legendre atual
			//Decide qual ponto de Lengendre e peso sera usado:
			switch (numPontos) {
			case 2:
				pl = tabelaLegendreN2[iPL][0];
				peso = tabelaLegendreN2[iPL][1];
				break;
			case 3:
				pl = tabelaLegendreN3[iPL][0];
				peso = tabelaLegendreN3[iPL][1];
				break;
			case 4:
				pl = tabelaLegendreN4[iPL][0];
				peso = tabelaLegendreN4[iPL][1];
				break;
			}
			//Calcula x(pl) - devido a mudança de variável para calcular no intervalo [a, b]
			double xi = (pl * (intervaloB - intervaloA) + intervaloA + intervaloB) / 2.0;
			//Acrescenta em resultadoSubintervalo o valor: peso * f(x(pl))
			resultadoSubintervalo += peso * funcao.calcular(xi);
		}
		resultadoAtual += resultadoSubintervalo;
		resultadoAtual = resultadoAtual * tamanhoIntervalo / 2.0;

		return resultadoAtual;
	}
	
	public static double calcularRegraTrapezio(Funcao funcao, double intervaloA, double intervaloB) {
		return (funcao.calcular(intervaloA) + funcao.calcular(intervaloB)) / 2.0;
	}
}
