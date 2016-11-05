/**
 * Created by sora on 16/11/03 -003.
 *九九乘法表三种输出方式
 */
public class MultiplicationTable {
    public void printMultiplicationTableByDoubleForLoop(){
        for(int i = 1; i < 10; i++){
            for(int j = 1; j <= i; j++){
                System.out.print(j + " * " + i + " = " + i*j + (i== j ? "\n": "\t"));
            }
        }
    }

    public void printMultiplicationTableBySingleForLoop(){
        for(int i = 1, j = 1; i < 10 ; j++){
            System.out.print(j + " * " + i + " = " + i*j + (i== j ? "\n": "\t"));
            if (i == j){
                i++;
                j = 0;
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
        System.out.print(j + " * " + i + " = " + i*j + (i== j ? "\n": "\t"));
    }
}
