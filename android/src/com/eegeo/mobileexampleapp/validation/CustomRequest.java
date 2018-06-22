package com.eegeo.mobileexampleapp.validation;

/**
 * Created by najhi on 28/05/2018.
 */

import java.io.UnsupportedEncodingException;
import java.util.Map;
import org.json.JSONException;
import org.json.JSONObject;
import com.android.volley.NetworkResponse;
import com.android.volley.ParseError;
import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.Response.ErrorListener;
import com.android.volley.Response.Listener;
import com.android.volley.toolbox.HttpHeaderParser;

public class CustomRequest extends Request<JSONObject>
{
    private Listener<JSONObject> m_listener;
    private Map<String, String> m_params;

    public CustomRequest(String url,
                         Map<String, String> params,
                         Listener<JSONObject> reponseListener,
                         ErrorListener errorListener) {
        super(Method.GET, url, errorListener);
        this.m_listener = reponseListener;
        this.m_params = params;
    }

    public CustomRequest(int method,
                         String url,
                         Map<String, String> params,
                         Listener<JSONObject> responseListener,
                         ErrorListener errorListener) {
        super(method, url, errorListener);
        this.m_listener = responseListener;
        this.m_params = params;
    }

    protected Map<String, String> getParams() throws com.android.volley.AuthFailureError
    {
        return m_params;
    };

    @Override
    protected Response<JSONObject> parseNetworkResponse(NetworkResponse response) {
        try {
            String jsonString = new String(response.data,
                    HttpHeaderParser.parseCharset(response.headers));
            return Response.success(new JSONObject(jsonString),
                    HttpHeaderParser.parseCacheHeaders(response));
        } catch (UnsupportedEncodingException e) {
            return Response.error(new ParseError(e));
        } catch (JSONException je) {
            return Response.error(new ParseError(je));
        }
    }

    @Override
    protected void deliverResponse(JSONObject response)
    {
        m_listener.onResponse(response);
    }
}