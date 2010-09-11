import Jama.Matrix;

public class DecomposicaoLU {
	
	public DecomposicaoLU(Matrix l, Matrix u) {
		super();
		L = l;
		U = u;
	}

	public Matrix getL() {
		return L;
	}

	public Matrix getU() {
		return U;
	}

	private Matrix L;
	private Matrix U;
}