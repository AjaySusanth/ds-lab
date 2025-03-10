import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class Main extends JFrame implements ActionListener {
  private JTextField textField;
  private JButton[] numberButtons;
  private JButton addButton, subtractButton, multiplyButton, divideButton, equalButton, clearButton, modulusButton;
  private double first, second, result;

  private char operator;

  public Main() {
    setTitle("Simple Calculator");
    setSize(300, 500);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    setLayout(new BorderLayout());
    textField = new JTextField();
    add(textField, BorderLayout.NORTH);
    textField.setFont(new Font("SansSerif", Font.PLAIN, 32));
    numberButtons = new JButton[10];
    for(int i=0;i<10;i++) {
      numberButtons[i] = new JButton(String.valueOf(i));
      numberButtons[i].addActionListener(this);
    }

    addButton = new JButton("+");
    subtractButton = new JButton("-");
    multiplyButton = new JButton("*");
    divideButton = new JButton("/");
    equalButton = new JButton("=");
    clearButton = new JButton("C");
    modulusButton=new JButton("%");

    JPanel buttonPanel = new JPanel();
    buttonPanel.setLayout(new GridLayout(5,4,10,10));

    buttonPanel.add(numberButtons[7]);
    buttonPanel.add(numberButtons[8]);;
    buttonPanel.add(numberButtons[9]);
    buttonPanel.add(addButton);
    buttonPanel.add(numberButtons[4]);
    buttonPanel.add(numberButtons[5]);
    buttonPanel.add(numberButtons[6]);
    buttonPanel.add(subtractButton);
    buttonPanel.add(numberButtons[1]);
    buttonPanel.add(numberButtons[2]);
    buttonPanel.add(numberButtons[3]);
    buttonPanel.add(multiplyButton);
    buttonPanel.add(clearButton);
    buttonPanel.add(numberButtons[0]);
    buttonPanel.add(equalButton);
    buttonPanel.add(divideButton);
    buttonPanel.add(modulusButton);

    addButton.addActionListener(this);
    subtractButton.addActionListener(this);
    multiplyButton.addActionListener(this);
    divideButton.addActionListener(this);
    equalButton.addActionListener(this);
    clearButton.addActionListener(this);
    modulusButton.addActionListener(this);

    add(buttonPanel,BorderLayout.CENTER);
    setVisible(true);

  }

  public static void main(String[] args) {
    new Main();
  }

  public void actionPerformed(ActionEvent e) {
    Object source = e.getSource();

    for(int i=0;i<10;i++) {
      if(source == numberButtons[i])
          textField.setText(textField.getText()+i);
    }

    if (source == addButton || source == subtractButton || source == multiplyButton || source == divideButton||source==modulusButton) {
      first = Double.parseDouble(textField.getText());
      operator = e.getActionCommand().charAt(0);
      textField.setText("");
    }
    if(source == equalButton) {
      second  = Double.parseDouble(textField.getText());
      try{
        result  = performOperation(first,second,operator);
        textField.setText(String.valueOf(result));
      } catch(ArithmeticException ex){
          textField.setText(String.valueOf(ex.getMessage()));
      }

    }
    if(source == clearButton) {
      textField.setText("");
      first=0;
      second=0;
      operator='\0';
    }
  }

  
  private double performOperation(double first,double second,char op) throws ArithmeticException {
    switch(op) {
      case '+': return first+second;
      case '-' : return first - second;
      case '*': return first * second;
      case '/':
        if(second == 0) throw new ArithmeticException("Division by zero");
        return first/second;
      default:return 0;
    }
  }
}