# Meu Repositório
Aqui estão todos os meus códigos que desenvolvo nos meus estudos em casa e na Universidade Federal de Campina Grande (Ufcg)




import java.util.Arrays;

public class QuickSortMediana3 {
    
    // Método para encontrar a mediana de três elementos
    private static int medianaDeTres(int[] arr, int low, int high) {
        int mid = (low + high) / 2;
        int a = arr[low], b = arr[mid], c = arr[high];

        // Retorna o índice da mediana
        if ((a <= b && b <= c) || (c <= b && b <= a))
            return mid;
        else if ((b <= a && a <= c) || (c <= a && a <= b))
            return low;
        else
            return high;
    }

    // Método para particionar o array
    private static int partition(int[] arr, int low, int high) {
        // Escolhe o pivô pela mediana de três e o move para a última posição
        int medianIndex = medianaDeTres(arr, low, high);
        swap(arr, medianIndex, high);
        int pivot = arr[high];

        int i = low - 1; // Índice do menor elemento
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr, i, j);
            }
        }

        // Coloca o pivô na posição correta
        swap(arr, i + 1, high);
        return i + 1; // Retorna a posição do pivô
    }

    // Método principal do QuickSort
    private static void quickSort(int[] arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    // Método auxiliar para trocar elementos no array
    private static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    // Método principal para testar
    public static void main(String[] args) {
        int[] arr = {10, 3, 8, 15, 6, 12, 2, 18, 7};
        quickSort(arr, 0, arr.length - 1);
        System.out.println(Arrays.toString(arr));
    }
}