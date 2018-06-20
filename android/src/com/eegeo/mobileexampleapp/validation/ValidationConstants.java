package com.eegeo.mobileexampleapp.validation;

/**
 * Created by najhi on 24/05/2018.
 */

public class ValidationConstants
{
    public static final String VALIDATION_BASE_URL = "https://mobilemc.hbmsu.ac.ae/api/ips/";
    public static final String KEY_IS_VALIDATED = "is_validated";

    public enum VALIDATION_STATUS
    {
        STATUS_IN_PROGRESS("STATUS_IN_PROGRESS"),
        STATUS_VERIFIED("STATUS_VERIFIED"),
        STATUS_EXPIRED("STATUS_EXPIRED"),
        STATUS_WRONG_CODE("STATUS_WRONG_CODE"),
        STATUS_ATTEMPTS_EXCEEDED("STATUS_ATTEMPTS_EXCEEDED"),
        STATUS_BLOCKED("STATUS_BLOCKED"),
        STATUS_ERROR("STATUS_ERROR");

        private String m_status;

        VALIDATION_STATUS(String status)
        {
            m_status = status;
        }

        public String value()
        {
            return m_status;
        }

        public boolean equals(String status)
        {
            return m_status.equals(status);
        }
    }
}
