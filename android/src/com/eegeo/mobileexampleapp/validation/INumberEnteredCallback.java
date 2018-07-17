package com.eegeo.mobileexampleapp.validation;

/**
 * Created by najhiullah on 13/03/2018.
 */

public interface INumberEnteredCallback
{
    void onNumberEntered(String preNumber, String mobileNumber, IOnErrorResponse onErrorResponse);
}
