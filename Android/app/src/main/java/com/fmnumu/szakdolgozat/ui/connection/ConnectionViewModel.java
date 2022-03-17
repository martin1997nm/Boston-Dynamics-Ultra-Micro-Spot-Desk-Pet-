package com.fmnumu.szakdolgozat.ui.connection;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

public class ConnectionViewModel extends ViewModel {

    private final MutableLiveData<String> mText;

    public ConnectionViewModel() {
        mText = new MutableLiveData<>();
        mText.setValue("This is connection fragment");
    }

    public LiveData<String> getText() {
        return mText;
    }
}