package com.eegeo.mobileexampleapp.validation;

/**
 * Created by najhiullah on 13/03/2018.
 */

public interface IValidationCodeScreenCallback
{
    void onValidationCodeEntered(String m_preNumber, String m_mobileNumber, int validationCode, IOnErrorResponse verificationCodeFailed);
    void onResendCodeRequest(String preNumber, String mobileNumber, IOnResendResponseReceivedCallback onResendResponseReceived);
    void onValidationCodeExpired();
}
