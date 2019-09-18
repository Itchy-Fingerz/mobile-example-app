package com.eegeo.mobileexampleapp.validation;

/**
 * Created by najhiullah on 13/03/2018.
 */

public interface ICredentialsEnteredCallback
{
    void onCredentialsEntered(String username, String password, IOnErrorResponse onErrorResponse);
}
