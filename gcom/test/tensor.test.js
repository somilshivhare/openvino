const { Tensor } = require('../lib/addon');
const assert = require('assert');

describe('Tensor.copyTo', () => {
    it('should copy data from one tensor to another', () => {
        const src = new Tensor(new Float32Array([1, 2, 3, 4]), [2, 2]);
        const dst = new Tensor(new Float32Array(4), [2, 2]);
        src.copyTo(dst);
        assert.deepStrictEqual(dst.getData(), new Float32Array([1, 2, 3, 4]));
    });

    it('should throw error for invalid arguments', () => {
        const tensor = new Tensor(new Float32Array(4), [2, 2]);
        
        // Test with no arguments
        assert.throws(() => tensor.copyTo(), /Invalid number of arguments/);
        
        // Test with non-tensor argument
        assert.throws(() => tensor.copyTo({}), /Argument must be a Tensor object/);
    });
}); 