// Autor: Luiz Junio <luisjuniorbr@gmail.com>
import java.util.Scanner;

public class Potenciacao {
   public static void main(String []args){
   double base, resultado = 1; 
   boolean erro;
   int expoente;
   
   Scanner read = new Scanner(System.in); 
   
   System.out.println("Esse programa calcula um n�mero elevado por outro. base^expoente.");
   System.out.print("Digite um n�mero real para a base: ");
   base = read.nextDouble();
   
   do{
      System.out.print("Digite um n�mero inteiro para o expoente: ");
      expoente = read.nextInt();
      erro = expoente < 0;
      if (erro) System.out.println("Valor inv�lido!");
   }while(erro);
   
   for(int cont = 0; cont < expoente; cont++ ){
      resultado *= base;
   }
   System.out.printf("O resultado de " + base + "^" + expoente + " = %.2f ", resultado );
 }  
}   