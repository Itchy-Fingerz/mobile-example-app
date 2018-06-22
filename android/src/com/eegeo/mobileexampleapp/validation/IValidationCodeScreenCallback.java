package com.eegeo.mobileexampleapp.validation;

/**
 * Created by najhiullah on 13/03/2018.
 */

public interface IValidationCodeScreenCallback
{
    void onValidationCodeEntered(int validationCode, String token, IOnErrorResponse verificationCodeFailed);
    void onResendCodeRequest(String phoneNumber, IOnResendResponseReceivedCallback onResendResponseReceived);
    void onValidationCodeExpired();
}
