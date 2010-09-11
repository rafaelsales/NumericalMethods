/**
 * Classe de teste dos métodos
 * @author Rafael de Castro Dantas Sales - rafaelcds@gmail.com
 */
public class Main {
	
	public static void main(String[] args) {
		final double g = 10;
		final double v0 = -2;
		final double y0 = 2000;
		final double tempoInicial = 0;
		final double tempoFinal = 20;
		double discretizacao = 0.1;
		if (args.length == 1) {
			discretizacao = Double.parseDouble(args[0]);
		}
		
		System.out.println("--- Valor Inicial ---");
		System.out.println("Equação Diferencial Ordinária: dy²/dt² = dv/dt = -g -v");
		System.out.println("Discretização = " + discretizacao);
		System.out.println("v0 = " + v0);
		System.out.println("y0 = " + y0);
		System.out.println("t = [" + tempoInicial + ", " + tempoFinal + "]");
		System.out.println();
		
		tarefa2(g, v0, y0, tempoInicial, tempoFinal, discretizacao);
		System.out.println();
		tarefa3(g, v0, y0, tempoInicial, tempoFinal, discretizacao);
		System.out.println();
		tarefa4(g, v0, y0, tempoInicial, tempoFinal, discretizacao);
		System.out.println();
		tarefa5(g, v0, y0, tempoInicial, tempoFinal, discretizacao);
	}

	public static void tarefa2(final double g, final double v0, final double y0, final double tempoInicial, final double tempoFinal, double discretizacao) {
		System.out.println("=> Tarefa 2 - Forward Euler");
		
		EDO dvdt = new EDO() {
			@Override
			public double calcular(double v, double t, int i) {
				return -g -v;
			}
		};
		final double[][] pontosVt = ValorInicial.forwardEuler(dvdt, v0, tempoInicial, tempoFinal, discretizacao);
		
		EDO dudt = new EDO() {
			@Override
			public double calcular(double y, double t, int i) {
				return pontosVt[1][i];
			}
		};
		
		System.out.println("Resultados:");
		double[][] pontosYt = ValorInicial.forwardEuler(dudt, y0, tempoInicial, tempoFinal, discretizacao);
		exibirPontos(pontosVt, "t", "v");
		System.out.println();
		exibirPontos(pontosYt, "t", "y");
	}
	
	public static void tarefa3(final double g, final double v0, final double y0, final double tempoInicial, final double tempoFinal, final double discretizacao) {
		System.out.println("=> Tarefa 3 - Backward Euler");
		
		EDO funcaoVtProximoPonto = new EDO() {
			@Override
			public double calcular(double v, double t, int i) {
				return (v - g * discretizacao) / (1 + discretizacao);
			}
		};
		final double[][] pontosVt = ValorInicial.backwardEuler(funcaoVtProximoPonto, v0, tempoInicial, tempoFinal, discretizacao);

		EDO funcaoYtProximoPonto = new EDO() {
			@Override
			public double calcular(double y, double t, int i) {
				return y + discretizacao * pontosVt[1][i];
			}
		};
		
		System.out.println("Resultados:");
		double[][] pontosYt = ValorInicial.backwardEuler(funcaoYtProximoPonto, y0, tempoInicial, tempoFinal, discretizacao);
		exibirPontos(pontosVt, "t", "v");
		System.out.println();
		exibirPontos(pontosYt, "t", "y");
	}
	
	public static void tarefa4(final double g, final double v0, final double y0, final double tempoInicial, final double tempoFinal, double discretizacao) {
		System.out.println("=> Tarefa 4 - Runge-Kutta de Terceira Ordem");
		
		EDO dvdt = new EDO() {
			@Override
			public double calcular(double v, double t, int i) {
				return -g -v;
			}
		};
		final double[][] pontosVt = ValorInicial.rungeKuttaTerceiraOrdem(dvdt, v0, tempoInicial, tempoFinal, discretizacao);
		
		EDO dudt = new EDO() {
			@Override
			public double calcular(double y, double t, int i) {
				return pontosVt[1][i];
			}
		};
		
		System.out.println("Resultados:");
		double[][] pontosYt = ValorInicial.rungeKuttaTerceiraOrdem(dudt, y0, tempoInicial, tempoFinal, discretizacao);
		exibirPontos(pontosVt, "t", "v");
		System.out.println();
		exibirPontos(pontosYt, "t", "y");
	}
	
	public static void tarefa5(final double g, final double v0, final double y0, final double tempoInicial, final double tempoFinal, double discretizacao) {
		System.out.println("=> Tarefa 5 - Método Preditor-Corretor");
		
		EDO dvdt = new EDO() {
			@Override
			public double calcular(double v, double t, int i) {
				return -g -v;
			}
		};
		final double[][] inicializacaoVt = ValorInicial.rungeKuttaTerceiraOrdem(dvdt, v0, tempoInicial, tempoInicial + 3 * discretizacao, discretizacao);
		final double[][] pontosVt = ValorInicial.preditorCorretorTerceiraOrdem(dvdt, inicializacaoVt, tempoInicial, tempoFinal, discretizacao);
		
		EDO dudt = new EDO() {
			@Override
			public double calcular(double y, double t, int i) {
				return pontosVt[1][i];
			}
		};
		
		System.out.println("Resultados:");
		double[][] inicializacaoYt = ValorInicial.rungeKuttaTerceiraOrdem(dudt, y0, tempoInicial, tempoInicial + 3 * discretizacao, discretizacao);
		double[][] pontosYt = ValorInicial.preditorCorretorTerceiraOrdem(dudt, inicializacaoYt, tempoInicial, tempoFinal, discretizacao);
		exibirPontos(pontosVt, "t", "v");
		System.out.println();
		exibirPontos(pontosYt, "t", "y");
	}
	
	public static void exibirPontos(double[][] pontos, String xLabel, String yLabel) {
		System.out.printf("%s = [", xLabel);
		for (int i = 0; i < pontos[0].length; i++) {
			if (i > 0) {
				System.out.print(", ");
			}
			System.out.print(pontos[0][i]);
		}
		System.out.println("]");
		
		System.out.printf("%s(%s) = [", yLabel, xLabel);
		for (int i = 0; i < pontos[0].length; i++) {
			if (i > 0) {
				System.out.print(", ");
			}
			System.out.print(pontos[1][i]);
		}
		System.out.println("]");
	}
}