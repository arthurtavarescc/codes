void mergeSort(int[] arr, int left, int right) {
    if (left < right) {
        int middle = (left + right) / 2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

void merge(int[] arr, int left, int middle, int right) {
    int[] temp = new int[right - left + 1];
    int i = left, j = middle + 1, k = 0;

    while (i <= middle && j <= right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }

    while (i <= middle) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (i = left, k = 0; i <= right; i++, k++) arr[i] = temp[k];
}

