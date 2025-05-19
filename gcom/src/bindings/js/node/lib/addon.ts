export interface Tensor {
    /**
     * Copies the data from this tensor to another tensor
     * @param tensor The target tensor to copy data to
     */
    copyTo(tensor: Tensor): void;
} 