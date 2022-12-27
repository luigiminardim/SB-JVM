

interface AllConstantPoolCasesInterface {
  int getAttribute();
}

class AllConstanPoolCases implements AllConstantPoolCasesInterface {
  final private int constantInteger = 100;
  final private float constantFloat = 101.0f;
  final private long constantLong = 102L;
  final private double constantDouble = 103.0;
  final private String constantString = "104";

  private int attribute = 1;

  public static void main(String[] args) {
    AllConstanPoolCases allConstanPoolCases = new AllConstanPoolCases();
    AllConstantPoolCasesInterface allConstantPoolCasesInterface = allConstanPoolCases;
    System.out.println(allConstantPoolCasesInterface.getAttribute());
    System.out.println(allConstanPoolCases.constantInteger);
    System.out.println(allConstanPoolCases.constantFloat);
    System.out.println(allConstanPoolCases.constantLong);
    System.out.println(allConstanPoolCases.constantDouble);
    System.out.println(allConstanPoolCases.constantString);
  }

  public int getAttribute() {
    return attribute;
  }
}