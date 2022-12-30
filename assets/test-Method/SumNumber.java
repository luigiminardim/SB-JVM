public class SumNumber {
    
    final private int first_attribute = 1;
    final public int second_attribute = 2;
    protected boolean third_attribute = true;
    protected char fourth_attribute = '4';

    public static void main(String[] args) {
        System.out.println(SumNumber.Soma(3,6));
        SumNumber somaClasse = new SumNumber();
        System.out.println(somaClasse.second_attribute);
    }   

    public static boolean TestaExcecao(){
        boolean resultado = false;
        try {
            int a[] = new int[2];
            System.out.println("Access element three :" + a[3]);
        } catch (ArrayIndexOutOfBoundsException e) {
            resultado = true;
        }
        return resultado;
    }

    public static int Soma(int a, int b){
        int c = a + b;
        return c;
    }
}
