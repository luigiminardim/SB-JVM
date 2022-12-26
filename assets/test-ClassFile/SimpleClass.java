class SimpleClass {
  private int attribute = 2;

  public static void main(String[] args) {
    SimpleClass simpleClass = new SimpleClass();
    System.out.println(simpleClass.getAttribute());
  }

  public int getAttribute() {
    return attribute;
  }
}
