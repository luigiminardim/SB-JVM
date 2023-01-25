public class SumNumber {
    
    final private int first_attribute = 1;
    final public int second_attribute = 13;
    protected boolean third_attribute = true;
    protected char fourth_attribute = '4';
    public int fifth_attribute = 33;
    static int sixth_attribute = 1998;

    static {System.out.println("99");}
    {System.out.println("100");}

    public static void main(String[] args) {
        //System.out.println(SumNumber.Soma(3,6));
        //SumNumber somaClasse = new SumNumber();
        //int teste_var = somaClasse.fifth_attribute;
        //somaClasse.fifth_attribute = somaClasse.fifth_attribute + teste_var;
        //System.out.println(somaClasse.second_attribute);
        //somaClasse.Subtracao(20, 10);
        int a = 10000;
        int b = 25;
        System.out.println("teste teste teste" + (a+b));
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
    
    public int Subtracao(int a, int b){
        int c = a - b;
        return c;
    }
}
