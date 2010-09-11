import java.util.ArrayList;
import java.util.List;

import Jama.Matrix;

/**
 * Classe que encapsula métodos que auxiliam no cálculo de autovalores e autovetores
 * @author Rafael de Castro Dantas Sales - rafaelcds@gmail.com
 */
public class AutovaloresAutovetores {

	/**
	 * Calcula o maior autovalor (em módulo) e o autovetor correspondente de uma matriz
	 * @param matriz
	 * @param autovetorInicial
	 * @param erro
	 * @return
	 */
	public static AutovalorAutovetor metodoPotencia(Matrix matriz, double[] autovetorInicial, double erro) {
		/**
		 * Passos da potencia regular:
		 * 1) Normaliza x0 = V/|V|
		 * 2) Yi = M*Xi-1
		 * 3) Xi = Yi/|Yi|
		 * 4) li = (T(Xi) * M * Xi) / (T(Xi) * Xi
		 * Repetir 2 à 4 enquanto li - li-1 < E
		 * OBS.: Xi é o autovetor correspondente ao autovalor li. Yi é um vetor.
		 */
		double avalorAnterior;
		double avalorNovo = 0;
		int i = 0;
		
		//Passo 1:
		Matrix matrizVetorInicial = MatrizUtil.vetorParaMatrix(autovetorInicial);
		Matrix avetor = MatrizUtil.normalizar(matrizVetorInicial);
		do {
			avalorAnterior = avalorNovo;
			//Passo 2:
			Matrix vetorY = matriz.times(avetor);
			//Passo 3:
			avetor = MatrizUtil.normalizar(vetorY);
			//Passo 4:
			Matrix matrixTranspostaAvetor = avetor.transpose();
			double avalorNumerador = matrixTranspostaAvetor.times(matriz).times(avetor).get(0, 0); 
			double avalorDenominador = matrixTranspostaAvetor.times(avetor).get(0, 0);
			avalorNovo = avalorNumerador / avalorDenominador;
			i++;
		} while (i == 1 || Math.abs(avalorNovo - avalorAnterior) > erro);

		AutovalorAutovetor autovalorAutovetor = new AutovalorAutovetor();
		autovalorAutovetor.autovalor = avalorNovo;
		autovalorAutovetor.autovetor = MatrizUtil.matrizParaVetor(avetor);
		return autovalorAutovetor;
	}
	
	/**
	 * Calcula o menor autovalor (em módulo) e o autovetor correspondente de uma matriz
	 * @param matriz
	 * @param autovetorInicial
	 * @param erro
	 * @return
	 */
	public static AutovalorAutovetor metodoPotenciaInverso(Matrix matriz, double[] autovetorInicial, double erro) {
		/**
		 * Poderiamos aplicar o método da potência regular utilizando a matriz inversa,
		 * porém, fazendo alguns alterações nos passos, eliminamos a necessidade de
		 * calcular a matriz inversa. 
		 * Passos da potencia inverso:
		 * 1) Normaliza x0 = V/|V|
		 * 2) Yi = M^(-1)*Xi-1  =>  M*yi = Xi-1 (Achamos yi resolvendo o sistema pelo método LU, pois o xi-1 muda a cada iteração)
		 * 3) Xi = Yi/|Yi|
		 * 4) li = (T(Xi) * M^(-1) * Xi) / (T(Xi) * Xi
		 * Repetir 2 à 4 enquanto li - li-1 < E
		 * OBS.: Xi é o autovetor correspondente ao autovalor li. Yi é um vetor.
		 */
		double avalorAnterior;
		double avalorNovo = 0;
		int i = 0;
		
		//Passo 1:
		Matrix matrizVetorInicial = MatrizUtil.vetorParaMatrix(autovetorInicial);
		Matrix avetorX = MatrizUtil.normalizar(matrizVetorInicial);
		//Prepara as matriz L e U reaproveitadas no passo 2:
		DecomposicaoLU luMatriz = MatrizUtil.getLU(matriz);
		Matrix lowerMatriz = luMatriz.getL();
		Matrix upperMatriz = luMatriz.getU();
		
		//Passo 2:
		/* M*yi = xi-1  =>  L*U*yi = xi-1
		 * a) Fazendo U*yi = Z, resolvemos primeiro L*Z = xi-1
		 * b) Obtido o vetor Z, resolvemos U*yi = Z
		 */
		Matrix vetorZ = MatrizUtil.resolverSubstituicao(lowerMatriz, avetorX);
		Matrix vetorY = MatrizUtil.resolverRetrosubstituicao(upperMatriz, vetorZ);
		do {
			avalorAnterior = avalorNovo;
			//Passo 3:
			avetorX = MatrizUtil.normalizar(vetorY);
			
			//Calcula yi+1:
			/* M*yi = xi-1  =>  L*U*yi = xi-1
			 * a) Fazendo U*yi = Z, resolvemos primeiro L*Z = xi-1
			 * b) Obtido o vetor Z, resolvemos U*yi = Z
			 */
			vetorZ = MatrizUtil.resolverSubstituicao(lowerMatriz, avetorX);
			vetorY = MatrizUtil.resolverRetrosubstituicao(upperMatriz, vetorZ);
			
			//Passo 4:
			//li = (T(Xi) * M^(-1) * Xi) / (T(Xi) * Xi  =>  li = (T(Xi) * yi+1) / (T(Xi) * Xi)
			Matrix matrixTranspostaAvetor = avetorX.transpose();
			double avalorNumerador = matrixTranspostaAvetor.times(vetorY).get(0, 0); 
			double avalorDenominador = matrixTranspostaAvetor.times(avetorX).get(0, 0);
			avalorNovo = avalorNumerador / avalorDenominador;
			i++;
		} while (i == 1 || Math.abs(avalorNovo - avalorAnterior) > erro);

		AutovalorAutovetor autovalorAutovetor = new AutovalorAutovetor();
		autovalorAutovetor.autovalor = 1.0 / avalorNovo;
		autovalorAutovetor.autovetor = MatrizUtil.matrizParaVetor(avetorX);
		return autovalorAutovetor;
	}
	
	/**
	 * Calcula um autovalor desejado e o autovetor correspondente de uma matriz baseado em um valor estimado do autovalor
	 * @param matriz
	 * @param autovetorInicial
	 * @param valorEstimado
	 * @param erro
	 * @return
	 */
	public static AutovalorAutovetor metodoPotenciaDeslocamento(Matrix matriz, double[] autovetorInicial, double valorEstimado, double erro) {
		/**
		 * Passos da potencia com deslocamento:
		 * 1) A' = A - u * I
		 * 2) Calcular li e Yi a partir do método da potencia inverso em A'
		 * OBS.: Xi é o autovetor correspondente ao autovalor li. Yi é um vetor.
		 * I é a matriz identidade. u é o valor estimado do autovalor.
		 */
		Matrix matrizIdentidade = Matrix.identity(matriz.getRowDimension(), matriz.getColumnDimension());
		Matrix matrizIdentidadeAlterada = matrizIdentidade.times(valorEstimado);
		Matrix matrizDeslocamento = matriz.minus(matrizIdentidadeAlterada);
		AutovalorAutovetor autovalorAutovetor = metodoPotenciaInverso(matrizDeslocamento, autovetorInicial, erro);
		autovalorAutovetor.autovalor += valorEstimado;
		return autovalorAutovetor;
	}
	
	/**
	 * Tridiagonaliza a matriz utilizando o método de Householder
	 * @param matriz
	 * @return
	 */
	public static Matrix metodoHouseholder(Matrix matriz) {
		Matrix matrizTridiagonalizada = matriz.copy();
		int ordem = matriz.getRowDimension();
		for (int k = 0; k < ordem - 2; k++) {
			//Obtém Hj de Mk-1:
			//Passos 1 e 2: Copia os elementos das linhas [k + 1, ordem - 1] da coluna k da matriz Mk-1 e atribui 0 para as linhas [0, k]
			Matrix subColunaK = matrizTridiagonalizada.getMatrix(0, ordem - 1, k, k);
			for (int i = 0; i <= k; i++) {
				subColunaK.set(i, 0, 0);
			}
			//Passo 3: Calcula o modulo do vetor obtido no passo 2
			double moduloSubcolunaK = MatrizUtil.calcularModuloVetor(subColunaK);
			
			//Passo 4: Cria uma matriz coluna com os elementos inicializados com 0, com exceção do elemento da linha (k + 1)
			Matrix colunaKLinha = new Matrix(ordem, 1, 0);
			int alfa = (int) Math.signum(matrizTridiagonalizada.get(k, k));
			colunaKLinha.set(k + 1, 0, (alfa * moduloSubcolunaK));
			
			//Passo 5: Calcula o vetor Nk = colunaK - colunaKLinha
			Matrix vetorNk = subColunaK.minus(colunaKLinha);
			
			//Passo 6: Normaliza o vetor Nk: nk = Nk / |Nk|
			vetorNk = MatrizUtil.normalizar(vetorNk);
			
			//Passo 7: Calcula a matriz de Householder: Hk = I - 2 * nk * T(nk)
			Matrix matrizIdentidade = Matrix.identity(ordem, ordem);
			Matrix matrizHk = matrizIdentidade.minus(vetorNk.times(vetorNk.transpose().times(2.0)));
			
			//Faz a transformação de similaridade: Mi+1 = T(P) * M * P. Como Hk é simétrica, T(Hk) = Hk
			matrizTridiagonalizada = matrizHk.times(matrizTridiagonalizada).times(matrizHk.transpose());
		}
		return matrizTridiagonalizada;
	}
	
	/**
	 * Diagonaliza a matriz utilizando o método de Jacobi para obter os autovalores e autovetores
	 * @param matriz
	 * @param erro
	 * @return
	 */
	public static List<AutovalorAutovetor> metodoJacobi(Matrix matriz, double erro) {
		int ordem = matriz.getRowDimension();
		Matrix matrizDiag = matriz.copy();
		Matrix matrizAVs = Matrix.identity(ordem, ordem);
		
		double normaM;
		do {
			for (int j = 0; j < ordem - 1; j++) {
				for (int i = j + 1; i < ordem; i++) {
					//Constuir P: matriz de rotação e ortonormal para zerar o M[i][j] tal que i != j
					Matrix p;
					{
						//Encontra angulo teta:
						double teta;
						if (matrizDiag.get(j, j) == matrizDiag.get(i, i)) {
							teta = Math.PI / 4.0;
						} else {
							//teta = 1/2 * arctg(2 * m[i][j] / (m[j][j] - m[i][i]))
							teta = 0.5 * Math.atan(2 * matrizDiag.get(i, j) / (matrizDiag.get(j, j) - matrizDiag.get(i, i)));
						}
						double senTeta = Math.sin(teta);
						double cosTeta = Math.cos(teta);
						p = Matrix.identity(ordem, ordem);
						p.set(j, j, cosTeta);
						p.set(i, i, cosTeta);
						p.set(i, j, senTeta);
						p.set(j, i, - senTeta);
					}
					Matrix pT = p.transpose();
					
					matrizDiag = pT.times(matrizDiag).times(p);
					matrizAVs = matrizAVs.times(p);
				}
			}
			
			//Calcula a norma de M: ||M|| = soma em módulo de m[i][j] tal que i != j
			normaM = MatrizUtil.calcularSomaModuloExcetoDiagonal(matrizDiag);
		} while (normaM > erro);
		
		List<AutovalorAutovetor> autovaloresAutovetores = new ArrayList<AutovalorAutovetor>(ordem);
		for (int j = 0; j < ordem; j++) {
			double[] autovetor = new double[ordem];
			for (int i = 0; i < ordem; i++) {
				autovetor[i] = matrizAVs.get(i, j);
			}
			AutovalorAutovetor autovalorAutovetor = new AutovalorAutovetor();
			autovalorAutovetor.autovalor = matrizDiag.get(j, j);
			autovalorAutovetor.autovetor = autovetor;
			autovaloresAutovetores.add(autovalorAutovetor);
		}
		return autovaloresAutovetores;
	}
	
	/**
	 * Diagonaliza a matriz utilizando o método decomposição QR para obter os autovalores e autovetores
	 * @param matriz
	 * @param erro
	 * @return
	 */
	public static List<AutovalorAutovetor> metodoQR(Matrix matriz, double erro) {
		int ordem = matriz.getRowDimension();
		Matrix matrizDiag = null;
		Matrix r = matriz.copy();
		Matrix matrizAVs = Matrix.identity(ordem, ordem);
		
		double normaM;
		do {
			Matrix qT = Matrix.identity(ordem, ordem);
			for (int j = 0; j < ordem - 1; j++) {
				for (int i = j + 1; i < ordem; i++) {
					//Constuir pT (transposta de P): matriz de rotação e ortonormal para zerar o M[i][j] tal que i != j
					Matrix pT;
					{
						//Encontra angulo teta:
						double teta;
						if (r.get(j, j) == 0) {
							teta = Math.PI / 2.0;
						} else {
							//teta = arctg(m[i][j] / (m[j][j])
							teta = Math.atan(r.get(i, j) / r.get(j, j));
						}
						double senTeta = Math.sin(teta);
						double cosTeta = Math.cos(teta);
						pT = Matrix.identity(ordem, ordem);
						pT.set(j, j, cosTeta);
						pT.set(i, i, cosTeta);
						pT.set(i, j, - senTeta);
						pT.set(j, i, senTeta);
					}
					r = pT.times(r);
					qT = pT.times(qT);
				}
			}

			//Se a matriz R não for triangular superior deve-se refazer a varredura:
			if (!MatrizUtil.triangularSuperior(r, erro)) {
				normaM = erro + 1;
				continue;
			}
			Matrix q = qT.transpose();

			//Calcula a matriz diagonal e a matriz dos autovetores
			matrizDiag = r.times(q);
			matrizAVs = matrizAVs.times(q);
			
			r = matrizDiag; //Prepara a matriz para a próxima iteração
			//Calcula a norma de M: ||M|| = soma em módulo de m[i][j] tal que i != j
			normaM = MatrizUtil.calcularSomaModuloExcetoDiagonal(matrizDiag);
		} while (normaM > erro);
		
		List<AutovalorAutovetor> autovaloresAutovetores = new ArrayList<AutovalorAutovetor>(ordem);
		for (int j = 0; j < ordem; j++) {
			double[] autovetor = new double[ordem];
			for (int i = 0; i < ordem; i++) {
				autovetor[i] = matrizAVs.get(i, j);
			}
			AutovalorAutovetor autovalorAutovetor = new AutovalorAutovetor();
			autovalorAutovetor.autovalor = matrizDiag.get(j, j);
			autovalorAutovetor.autovetor = autovetor;
			autovaloresAutovetores.add(autovalorAutovetor);
		}
		return autovaloresAutovetores;
	}
}
