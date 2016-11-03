/**
 * Created by sora on 16/11/03 -003.
 */
public class MultiplicationTable {
    public void printMultiplicationTableByDoubleForLoop(){
        for(int i = 1; i < 10; i++){
            for(int j = 1; j <= i; j++){
                System.out.print(i + " * " + j + " = " + i*j + "\t");
            }
            System.out.println();
        }
    }

    public void printMultiplicationTableBySingleForLoop(){
        for(int i = 1, j = 1; i < 10 ; j++){
            System.out.print(i + " * " + j + " = " + i*j + "\t");
            if (i == j){
                i++;
                j = 1;
                System.out.println();
            }
        }
    }
    public void printMultiplicationTableByNoneForLoop(){
        printMultiplicationTableByNoneForLoop(9, 9);
    }
    private void printMultiplicationTableByNoneForLoop(int i, int j){
        if(i == 0 && j == 0) {
            return;
        }else{
            if( j == 1) {
                printMultiplicationTableByNoneForLoop(i - 1, i - 1);
            }else{
                printMultiplicationTableByNoneForLoop(i, j-1);
            }
        }
        System.out.print(j + " * " + i + " = " + i*j + "\t");
        if(i == j){
            System.out.println();
        }
    }
}
