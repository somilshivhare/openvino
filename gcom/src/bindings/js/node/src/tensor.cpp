class Tensor : public Napi::ObjectWrap<Tensor> {
public:
    // ... existing code ...
    
    // Add copyTo method declaration
    void copyTo(const Napi::CallbackInfo& info);
    
    // ... existing code ...
};

void Tensor::copyTo(const Napi::CallbackInfo& info) {
    if (info.Length() != 1) {
        Napi::Error::New(info.Env(), "Invalid number of arguments").ThrowAsJavaScriptException();
        return;
    }

    if (!info[0].IsObject()) {
        Napi::Error::New(info.Env(), "Argument must be a Tensor object").ThrowAsJavaScriptException();
        return;
    }

    Napi::Object obj = info[0].As<Napi::Object>();
    if (!obj.InstanceOf(Tensor::constructor.Value())) {
        Napi::Error::New(info.Env(), "Argument must be a Tensor object").ThrowAsJavaScriptException();
        return;
    }

    Tensor* other = Napi::ObjectWrap<Tensor>::Unwrap(obj);
    _tensor->copy_to(*other->_tensor);
}

// In the constructor initialization
Napi::Function func = DefineClass(env, "Tensor", {
    // ... existing methods ...
    InstanceMethod("copyTo", &Tensor::copyTo),
    // ... existing methods ...
});

// Add the copyTo method to the prototype
Napi::FunctionReference& Tensor::constructor = Napi::Persistent(func);
Tensor::constructor.SuppressDestruct();
Tensor::constructor.Value().Set("copyTo", Napi::Function::New(env, Tensor::copyTo));

class TensorWrap : public Napi::ObjectWrap<TensorWrap> {
public:
    // ... existing code ...
    void copyTo(const Napi::CallbackInfo& info);
    // ... existing code ...
};

void TensorWrap::copyTo(const Napi::CallbackInfo& info) {
    if (info.Length() != 1) {
        reportError(info.Env(), "Invalid number of arguments");
        return;
    }

    if (!info[0].IsObject()) {
        reportError(info.Env(), "Argument must be a Tensor object");
        return;
    }

    Napi::Object obj = info[0].As<Napi::Object>();
    if (!obj.InstanceOf(TensorWrap::get_class(info.Env()))) {
        reportError(info.Env(), "Argument must be a Tensor object");
        return;
    }

    TensorWrap* other = Napi::ObjectWrap<TensorWrap>::Unwrap(obj);
    _tensor.copy_to(other->_tensor);
}

Napi::Function TensorWrap::get_class(Napi::Env env) {
    return DefineClass(env,
                       "TensorWrap",
                       {InstanceAccessor<&TensorWrap::get_data, &TensorWrap::set_data>("data"),
                        InstanceMethod("getData", &TensorWrap::get_data),
                        InstanceMethod("getShape", &TensorWrap::get_shape),
                        InstanceMethod("getElementType", &TensorWrap::get_element_type),
                        InstanceMethod("getSize", &TensorWrap::get_size),
                        InstanceMethod("isContinuous", &TensorWrap::is_continuous),
                        InstanceMethod("copyTo", &TensorWrap::copyTo)});
} 