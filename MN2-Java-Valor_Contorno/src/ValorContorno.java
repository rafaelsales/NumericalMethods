import Jama.Matrix;

public class ValorContorno {

	private ValorContorno() {
	}

	public static void diferencasFinitas(int particoes) {
		int n = particoes - 1;
		int m = n * n;
		double lX, lY, uB, uT, uL, uR, pXY, deltaX, deltaY;

		uB = uT = uL = uR = 0;
		lX = lY = 2;
		pXY = -2;

		deltaX = deltaY = lX / particoes;

		double[][] coeficientes = new double[m][m];
		double[] termosIndependentes = new double[m];

		//Obtém os delta x e y da segunda derivada:
		double deltaX2d = deltaX * deltaX;
		double deltaY2d = deltaY * deltaY;

		double delta = deltaX2d * deltaY2d;

		for (int j = 0; j < m; ++j) {
			for (int i = 0; i < m; ++i) {
				coeficientes[i][j] = 0;
			}
		}

		for (int j = 0; j < m; ++j) {
			for (int i = 0; i < m; ++i) {
				if (i == j) {
					coeficientes[i][j] = -2 * ((deltaY2d + deltaX2d) / delta);
				}
				if (i - j == 1 || j - i == 1) {
					coeficientes[i][j] = 1 / deltaX2d;
				}
				if (i - j == n || j - i == n) {
					coeficientes[i][j] = 1 / deltaY2d;
				}
			}
		}

		// Corrige a falta do elemento anterior
		for (int i = n; i < (m - 1); i = i + n) {
			coeficientes[i][i - 1] = 0;
		}

		// Corrige a falta do elemento posterior
		for (int i = n - 1; i < (m - 1); i = i + n) {
			coeficientes[i][i + 1] = 0;
		}

		// Define os termos independentes
		for (int i = 0; i < m; ++i) {
			termosIndependentes[i] = pXY;
		}

		// Calcula a solução do sistema:
		Matrix solucao = new Matrix(coeficientes).solve(MatrizUtil.vetorParaMatrix(termosIndependentes));

		System.out.println("Solução:");
		
		for (int i = 0; i < m; i++) {
			System.out.printf("u%d %f\n", i, solucao.get(i, 0));
		}
	}
}
