import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import Jama.Matrix;

public class MatrizUtil {

	public static double[][] lerMatrizDeArquivo(String caminho) throws Exception {
		FileReader fileReader = null;
		try {
			fileReader = new FileReader(caminho);
			BufferedReader bufferedReader = new BufferedReader(fileReader);
			String linhaStr = bufferedReader.readLine();
			if (linhaStr == null) {
				throw new Exception("Arquivo inválido");
			}
			// Separa o numero de linhas do de colunas. Formato: 200x300
			String[] cabecalho = linhaStr.split("x");
			int numLinhas = Integer.parseInt(cabecalho[0]);
			int numColunas = Integer.parseInt(cabecalho[1]);
			double[][] matriz = new double[numLinhas][numColunas];

			for (int i = 0; i < numLinhas; i++) {
				linhaStr = bufferedReader.readLine();
				String[] valoresColunas = linhaStr.split(" ");
				for (int j = 0; j < numColunas; j++) {
					matriz[i][j] = Double.parseDouble(valoresColunas[j]);
				}
			}
			return matriz;
		} catch (FileNotFoundException e) {
			throw new FileNotFoundException("Arquivo não encontrado: " + caminho);
		} catch (IOException e) {
			throw new IOException("Erro na leitura do arquivo", e);
		} finally {
			fileReader.close();
		}
	}

	public static String matrizParaString(double[][] matriz) {
		StringBuilder string = new StringBuilder();
		for (int i = 0; i < matriz.length; i++) {
			for (int j = 0; j < matriz[i].length; j++) {
				if (j > 0) {
					string.append("  ");
				}
				string.append(matriz[i][j]);
			}
			string.append("\n");
		}
		return string.toString();
	}

	public static String matrizParaString(Matrix matriz) {
		return matrizParaString(matriz.getArray());
	}

	public static void exibirVetor(double[] vetor) {
		vetorParaMatrix(vetor).transpose().print(5, 4);
	}

	public static void exibirMatriz(double[][] matriz) {
		new Matrix(matriz).print(5, 4);
	}

	public static void exibirMatriz(Matrix matriz) {
		matriz.print(5, 4);
	}

	public static double calcularModuloVetor(double[] vetor) {
		double modulo = 0;
		for (int i = 0; i < vetor.length; i++) {
			modulo += vetor[i] * vetor[i];
		}
		return Math.sqrt(modulo);
	}

	public static double calcularModuloVetor(Matrix matrixVetor) {
		return calcularModuloVetor(matrizParaVetor(matrixVetor));
	}

	public static double[] normalizar(double[] vetor) {
		double[] vetorNormalizado = new double[vetor.length];
		double modulo = calcularModuloVetor(vetor);
		for (int i = 0; i < vetor.length; i++) {
			vetorNormalizado[i] = vetor[i] / modulo;
		}
		return vetorNormalizado;
	}

	public static Matrix normalizar(Matrix matrizVetor) {
		return matrizVetor.times(1.0 / calcularModuloVetor(matrizVetor));
	}

	public static Matrix vetorParaMatrix(double[] vetor) {
		double[][] matriz = new double[vetor.length][1];
		for (int i = 0; i < matriz.length; i++) {
			matriz[i][0] = vetor[i];
		}
		return new Matrix(matriz);
	}

	public static double[] matrizParaVetor(Matrix matriz) {
		return matriz.getColumnPackedCopy();
	}

	public static double[] matrizParaVetor(double[][] matriz) {
		return new Matrix(matriz).getColumnPackedCopy();
	}

	public static Matrix resolverSubstituicao(Matrix matrizTriangularInferior, Matrix termosIndependentes) {
		Matrix solucao = new Matrix(matrizTriangularInferior.getRowDimension(), 1);
		for (int i = 0; i < matrizTriangularInferior.getRowDimension(); i++) {
			double valor = 0;
			for (int j = i - 1; j >= 0; j--) {
				valor += matrizTriangularInferior.get(i, j) * solucao.get(j, 0);
			}
			valor = (termosIndependentes.get(i, 0) - valor) / matrizTriangularInferior.get(i, i);
			solucao.set(i, 0, valor);
		}
		return solucao;
	}

	public static Matrix resolverRetrosubstituicao(Matrix matrizTriangularSuperior, Matrix termosIndependentes) {
		Matrix solucao = new Matrix(matrizTriangularSuperior.getRowDimension(), 1);
		for (int i = matrizTriangularSuperior.getRowDimension() - 1; i >= 0; i--) {
			double valor = 0;
			for (int j = i + 1; j < matrizTriangularSuperior.getRowDimension(); j++) {
				valor += matrizTriangularSuperior.get(i, j) * solucao.get(j, 0);
			}
			valor = (termosIndependentes.get(i, 0) - valor) / matrizTriangularSuperior.get(i, i);
			solucao.set(i, 0, valor);
		}
		return solucao;
	}

	public static DecomposicaoLU getLU(Matrix matriz) {
		double mulitplicador;
		int m = matriz.getRowDimension();
		int n = matriz.getColumnDimension();
		double[][] l = new double[m][n];
		double[][] u = new double[m][n];

		for (int i = 0; i < m; i++) {
			l[i][i] = 1;
			for (int j = 0; j < n; j++) {
				u[i][j] = matriz.get(i, j);
			}
		}

		for (int j = 0; j < n - 1; j++) {
			for (int i = j + 1; i < m; i++) {
				mulitplicador = (u[i][j]) / u[j][j];
				l[i][j] = mulitplicador;
				// Calcula (linha i) - (linha j) * mj:
				for (int k = 0; k < m; k++) {
					u[i][k] -= u[j][k] * mulitplicador;
				}
			}
		}

		return new DecomposicaoLU(new Matrix(l), new Matrix(u));
	}

	/**
	 * Calcula a norma de M: ||M|| = soma em módulo de m[i][j] tal que i != j 
	 * @param matriz
	 * @return
	 */
	public static double calcularSomaModuloExcetoDiagonal(Matrix matriz) {
		double norma = 0.0;
		for (int i = 0; i < matriz.getRowDimension(); i++) {
			for (int j = 0; j < matriz.getColumnDimension(); j++) {
				if (i != j) {
					norma += Math.abs(matriz.get(i, j));
				}
			}
		}
		return norma;
	}
	
	public static boolean triangularSuperior(Matrix matriz, double erro) {
		for (int i = 1; i < matriz.getRowDimension(); i++) {
			for (int j = 0; j < i; j++) {
				if (Math.abs(matriz.get(i, j)) > erro) {
					return false;
				}
			}
		}
		return true;
	}
}
