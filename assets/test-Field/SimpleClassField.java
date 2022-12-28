class SimpleClass {
  private int attribute = 1;
  public int second_attribute = 2;
  protected boolean third_attribute = true;
  protected char fourth_attribute = '4';


  public static void main(String[] args) {
    SimpleClass simpleClass = new SimpleClass();
    System.out.println(simpleClass.getAttribute());
  }

  public int getAttribute() {
    return attribute;
  }
}
