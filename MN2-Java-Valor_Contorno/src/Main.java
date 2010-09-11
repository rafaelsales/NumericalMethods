import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner scannerNumber = new Scanner(System.in);

		System.out.println("--- Problema de Valor de Contorno ---");
		System.out.println("--- Solução por Diferenças Finitas ---");
		System.out.print("Número de partes: ");
		int h = scannerNumber.nextInt();
		
		ValorContorno.diferencasFinitas(h);
	}
}
