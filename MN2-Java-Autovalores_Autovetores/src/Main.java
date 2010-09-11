import java.util.List;
import java.util.Scanner;

import Jama.Matrix;

/**
 * Classe de teste dos métodos
 * @author Rafael de Castro Dantas Sales - rafaelcds@gmail.com
 */
public class Main {
	public static void main(String[] args) {
		try {
			Scanner scannerInt = new Scanner(System.in);
			Scanner scannerLine = new Scanner(System.in);
			String caminhoArquivoMatriz = "matriz.txt";
			String caminhoArquivoAutovetorChute = "vetor_chute.txt";
			double erro = 0.001;
			
			Matrix matriz = new Matrix(MatrizUtil.lerMatrizDeArquivo(caminhoArquivoMatriz));
			double[] autovetorChute = MatrizUtil.matrizParaVetor(MatrizUtil.lerMatrizDeArquivo(caminhoArquivoAutovetorChute));

			System.out.println("Erro: " + erro);
			if (matriz.getRowDimension() <= 4) {
				System.out.println("Matriz de entrada:");
				MatrizUtil.exibirMatriz(matriz);
			}
			
			int opcao;
			do {
				System.out.println("--- Autovalores e Autovetores ---");
				System.out.println(" 0 - Executar todas as tarefas listadas abaixo");
				System.out.println(" 1 - Tarefa 5: Potência Regular");
				System.out.println(" 2 - Tarefa 5: Potência Inverso");
				System.out.println(" 3 - Tarefa 5: Potência Deslocamento");
				System.out.println(" 4 - Tarefa 6: Householder");
				System.out.println(" 5 - Tarefa 7: Jacobi");
				System.out.println(" 6 - Tarefa 8: QR");
				System.out.println(" 7 - Sair");
				
				System.out.print("Digite o número da opção: ");
				opcao = scannerInt.nextInt();
				System.out.println();
				
				switch (opcao) {
				case 0:
				case 1:
					System.out.println("---");
					tarefa5PotenciaRegular(matriz, autovetorChute, erro);
					if (opcao != 0) {
						break;
					}
				case 2:
					System.out.println("---");
					tarefa5PotenciaInverso(matriz, autovetorChute, erro);
					if (opcao != 0) {
						break;
					}
				case 3:
					System.out.println("---");
					tarefa5PotenciaDeslocamento(matriz, autovetorChute, erro);
					if (opcao != 0) {
						break;
					}
				case 4:
					System.out.println("---");
					tarefa6TridiagonalizarHouseholder(matriz);
					if (opcao != 0) {
						break;
					}
				case 5:
					System.out.println("---");
					tarefa7Jacobi(matriz, erro);
					if (opcao != 0) {
						break;
					}
				case 6:
					System.out.println("---");
					tarefa8QR(matriz, erro);
					break;
				case 7:
					break;
				default:
					System.out.println("Opção inválida!\n");
					break;
				}
				if (opcao != 7) {
					System.out.println("=> Pressione ENTER para continuar");
					scannerLine.nextLine();
				}
			} while (opcao != 7);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void tarefa5PotenciaRegular(Matrix matriz, double[] autovetorChute, double erro) throws Exception {
		System.out.println("=> Tarefa 5 - Metodo da potencia regular (encontra o maior autovalor)");
		if (matriz.getRowDimension() <= 4) {
			System.out.println("Chute inicial: ");
			MatrizUtil.exibirVetor(autovetorChute);
		}
		
		AutovalorAutovetor autovalorAutovetor = AutovaloresAutovetores.metodoPotencia(matriz, autovetorChute, erro);
		System.out.println("Autovalor: " + autovalorAutovetor.autovalor);
		System.out.println("Autovetor:");
		MatrizUtil.exibirVetor(autovalorAutovetor.autovetor);	
	}
	
	public static void tarefa5PotenciaInverso(Matrix matriz, double[] autovetorChute, double erro) throws Exception {
		System.out.println("=> Tarefa 5 - Metodo da potencia inversa (encontra o menor autovalor)");
		if (matriz.getRowDimension() <= 4) {
			System.out.println("Chute inicial: ");
			MatrizUtil.exibirVetor(autovetorChute);
		}
		
		AutovalorAutovetor autovalorAutovetor = AutovaloresAutovetores.metodoPotenciaInverso(matriz, autovetorChute, erro);
		System.out.println("Autovalor: " + autovalorAutovetor.autovalor);
		System.out.println("Autovetor:");
		MatrizUtil.exibirVetor(autovalorAutovetor.autovetor);
	}
	
	public static void tarefa5PotenciaDeslocamento(Matrix matriz, double[] autovetorChute, double erro) throws Exception {
		int autovalorEstimado = 3;
		System.out.println("=> Tarefa 5 - Metodo da potencia com deslocamento");
		System.out.println("Valor estimado do autovalor: " + autovalorEstimado);
		if (matriz.getRowDimension() <= 4) {
			System.out.println("Chute inicial: ");
			MatrizUtil.exibirVetor(autovetorChute);
		}
		
		AutovalorAutovetor autovalorAutovetor = AutovaloresAutovetores.metodoPotenciaDeslocamento(matriz, autovetorChute, autovalorEstimado, erro);
		System.out.println("Autovalor: " + autovalorAutovetor.autovalor);
		System.out.println("Autovetor:");
		MatrizUtil.exibirVetor(autovalorAutovetor.autovetor);
	}

	public static void tarefa6TridiagonalizarHouseholder(Matrix matriz) {
		System.out.println("=> Tarefa 6 - Metodo de Householder para tridiagonalizar uma matriz");

		Matrix matrizTridiagonalizada = AutovaloresAutovetores.metodoHouseholder(matriz);
		System.out.println("Matriz tridiagonalizada:");
		MatrizUtil.exibirMatriz(matrizTridiagonalizada);
	}
	
	public static void tarefa7Jacobi(Matrix matriz, double erro) {
		System.out.println("=> Tarefa 7 - Metodo de Jacobi para diagonalizar uma matriz");
		
		List<AutovalorAutovetor> autovaloresAutovetores = AutovaloresAutovetores.metodoJacobi(matriz, erro);
		int i = 1;
		for (AutovalorAutovetor autovalorAutovetor : autovaloresAutovetores) {
			System.out.println("Autovalor " + i + ": " + autovalorAutovetor.autovalor);
			System.out.println("Autovetor " + i + ": ");
			MatrizUtil.exibirVetor(autovalorAutovetor.autovetor);
			i++;
		}
	}
	
	public static void tarefa8QR(Matrix matriz, double erro) {
		System.out.println("=> Tarefa 8 - Metodo QR para diagonalizar uma matriz");
		
		List<AutovalorAutovetor> autovaloresAutovetores = AutovaloresAutovetores.metodoQR(matriz, erro);
		int i = 1;
		for (AutovalorAutovetor autovalorAutovetor : autovaloresAutovetores) {
			System.out.println("Autovalor " + i + ": " + autovalorAutovetor.autovalor);
			System.out.println("Autovetor " + i + ": ");
			MatrizUtil.exibirVetor(autovalorAutovetor.autovetor);
			i++;
		}
	}
	
	public static void testar(Matrix matriz, AutovalorAutovetor autovalorAutovetor) {
		System.out.println("Calcula: (M * Autovetor) / Autovalor). Resultado deve ser igual ao autovetor");
		MatrizUtil.exibirMatriz(matriz.times(MatrizUtil.vetorParaMatrix(autovalorAutovetor.autovetor)).times(1.0 / autovalorAutovetor.autovalor));
	}
}