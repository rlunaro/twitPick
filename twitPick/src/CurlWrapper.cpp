/*
 * Copyright 2018 Raul Luna
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/*
 * TwitterPicker.cpp
 *
 * rluna
 * Jul 19, 2018
 *
 */

#include "CurlWrapper.h"

// this declaration will keep track of the
// global definitions
CurlWrapper::GlobalToken CurlWrapper::globalToken;



CurlWrapper::CurlWrapper()
{
	curlHandle = curl_easy_init();
	if( curlHandle == nullptr )
		throw std::runtime_error("Could not init easy_init");
	curlVersion = curl_version();
	memset( lastErrorMsg, 0, CURL_ERROR_SIZE );
	curl_easy_setopt( curlHandle, CURLOPT_ERRORBUFFER, lastErrorMsg );
	requestHeaderList = nullptr;
	postParameterValues = "";
	getParameterValues = "";
}


CurlWrapper::~CurlWrapper()
{
	curl_slist_free_all( requestHeaderList );

	curl_easy_cleanup( curlHandle );
}

void CurlWrapper::reset()
{
	curl_slist_free_all( requestHeaderList );
	requestHeaderList = nullptr;
	postParameterValues = "";
	getParameterValues = "";

	curl_easy_reset( curlHandle );
}

CURL *CurlWrapper::getCurlHandle()
{
	return curlHandle;
}

EncodedUrl CurlWrapper::getEncodedUrl( std::string url )
{
	return EncodedUrl( curlHandle, url );
}

EncodedUrl CurlWrapper::getEncodedUrl( char *url, size_t size )
{
	return EncodedUrl( curlHandle, url, size );
} // getEncodedUrl

void CurlWrapper::setCookiesFilename( const std::string& cookiesFilename )
{
	CurlWrapper::cookiesFilename = cookiesFilename;
}

void CurlWrapper::setVerbose( bool verbose )
{
	if( verbose )
		curl_easy_setopt( curlHandle, CURLOPT_VERBOSE, 1L );
	else
		curl_easy_setopt( curlHandle, CURLOPT_VERBOSE, 0L );
} // setVerbose

void CurlWrapper::setProgress( bool progress )
{
	if( progress )
		curl_easy_setopt( curlHandle, CURLOPT_NOPROGRESS, 0 );
	else
		curl_easy_setopt( curlHandle, CURLOPT_NOPROGRESS, 1L );
} // setProgress


/**
 * Function to get the contents of the page.
 *
 * <p>
 * In the fourth parameter I will receive a pointer
 * to this object (@see CurlWrapper) to get the
 * contents loaded back into the object. </p>
 */
size_t getContentsCallback(char *ptr,
					  size_t size,
					  size_t nmemb,
					  void *userdata)
{
	if( userdata != nullptr )
	{
		CurlWrapper *object = (CurlWrapper *)userdata;
		object->loadContents( ptr, size, nmemb );
	}
	return size * nmemb;
} // loadContents

void CurlWrapper::loadContents(char *ptr,
									  size_t size,
									  size_t nmemb)
{
    contents.append( ptr, ptr + (nmemb * size) );
} // loadContents

/**
 * Function to get the contents of the headers.
 *
 */
size_t getHeaderCallback(char *buffer,
						 size_t size,
						 size_t nitems,
						 void *userdata)
{
	if( userdata != nullptr )
	{
		CurlWrapper *object = (CurlWrapper *)userdata;
		object->loadHeaderInfo( buffer, size, nitems );
	}
	return size * nitems;
} // getHeaderCallback

void CurlWrapper::clearResponseHeaderInfo()
{
	rawResponseHeaders.clear();
} // clearHeaderInfo

void CurlWrapper::clearContentInfo()
{
    contents.clear();
}

void CurlWrapper::loadHeaderInfo(char *buffer,
								size_t size,
								size_t nitems )
{
	rawResponseHeaders.push_back( std::string(buffer) );
} // loadHeaderInfo


std::vector<HttpHeader> CurlWrapper::getResponseHeaders()
{
	std::vector<HttpHeader> retVal;
	for( std::string rawHeader : rawResponseHeaders )
	{
		retVal.push_back( HttpHeader( rawHeader ) );
	}
	return retVal;
} // getHeaderValue

/**
 * Return the value of a specific header, or the empty string if not found
 */
std::string CurlWrapper::getHeaderValue( std::string headerName )
{
	std::string retVal = "";
	for( std::string rawHeader : rawResponseHeaders )
	{
		HttpHeader header( rawHeader );
		if( header.getName() == headerName )
		{
			retVal = header.getValue();
			break;
		}
	}
	return retVal;

}

void CurlWrapper::addRequestHeader( HttpHeader header )
{
	requestHeaderList = curl_slist_append( requestHeaderList, header.toString().c_str() );
}

void CurlWrapper::addPostParameter( HttpParameter parameter )
{
	postParameterList.push_back( parameter );
}

void CurlWrapper::addGetParameter( HttpParameter parameter )
{
	getParameterList.push_back( parameter );
}

void CurlWrapper::easyPerform()
{
	CURLcode result = curl_easy_perform( curlHandle );
	if( result != CURLE_OK )
	{
		throw TwitPickException( std::string( "Error in easyPerform: " ) + std::string( lastErrorMsg ) );
	}
} // easyPerform

std::string CurlWrapper::getContents()
{
	return contents;
}

long CurlWrapper::getStatusCode()
{
	// get the status code
	long statusCode;
	CURLcode result;

	result = curl_easy_getinfo( curlHandle, CURLINFO_RESPONSE_CODE, &statusCode );
	if( result != CURLE_OK )
	{
		throw std::runtime_error( std::string( "Error in getStatusCode: " ) + std::string( lastErrorMsg ) );
	}
	return statusCode;

} // getStatusCode

void CurlWrapper::commonHttpConfig()
{
	// peer verification (can be skipped
	curl_easy_setopt( curlHandle, CURLOPT_SSL_VERIFYPEER, 1L );

	// verify hostname??
	curl_easy_setopt( curlHandle, CURLOPT_SSL_VERIFYHOST, 2L );

	// to get the contents of the page
	curl_easy_setopt( curlHandle, CURLOPT_WRITEDATA, this );
	curl_easy_setopt( curlHandle, CURLOPT_WRITEFUNCTION, getContentsCallback );

	// to get the contents of the header
	curl_easy_setopt( curlHandle, CURLOPT_HEADERDATA, this );
	curl_easy_setopt( curlHandle, CURLOPT_HEADERFUNCTION, getHeaderCallback );

} // commonHttpGetConfig

void CurlWrapper::httpGet(  std::string protocol,
						  std::string host,
						  std::string path  )
{
	// we have to add the request parameters in the url,
	// because this is a GET request
	injectGetParameters();

	std::string url = protocol + "://" + host + "/" + path + getParameterValuesAsUrl();
	curl_easy_setopt( curlHandle, CURLOPT_URL, url.c_str() );
	curl_easy_setopt( curlHandle, CURLOPT_HTTPGET, 1L );

	// cookies
	curl_easy_setopt( curlHandle, CURLOPT_COOKIEJAR, "cookies.txt" );
	curl_easy_setopt( curlHandle, CURLOPT_COOKIEFILE, "cookies.txt" );

	commonHttpConfig();
	clearResponseHeaderInfo();
	clearContentInfo();

	injectRequestHeaders();

	easyPerform();

//	// print out the headers returned in the response (for debug purposes)
//	std::vector<HttpHeader> responseHeaders = getResponseHeaders();
//	for( auto header : responseHeaders )
//	{
//		std::cout << header.getName() << ": " << header.getValue() << std::endl;
//	}

} // httpGet

void CurlWrapper::httpPost( std::string protocol,
						   std::string host,
						   std::string path )
{
	std::string url = protocol + "://" + host + "/" + path;
	curl_easy_setopt( curlHandle, CURLOPT_URL, url.c_str() );

	commonHttpConfig();
	clearResponseHeaderInfo();
	clearContentInfo();

	injectRequestHeaders();

	injectPostParameters();

	easyPerform();

//	// print out the headers returned in the response (for debug purposes)
//	std::vector<HttpHeader> responseHeaders = getResponseHeaders();
//	for( auto header : responseHeaders )
//	{
//		std::cout << header.getName() << ": " << header.getValue() << std::endl;
//	}


}

void CurlWrapper::injectRequestHeaders( )
{
    CURLcode res;

    /* set our custom set of headers */
	res = curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, requestHeaderList);
	if( res != CURLE_OK )
	{
		throw TwitPickException("Error setting headers in injectRequestHeaders");
	}

}

void CurlWrapper::injectPostParameters()
{
	bool includeAmp = false;
	postParameterValues = "";
	for( HttpParameter parameter : postParameterList )
	{
		if(includeAmp)
			postParameterValues.push_back('&');
		postParameterValues += parameter.getEscapedNameValue( curlHandle );
		includeAmp = true;
	}
	curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS,
										postParameterValues.c_str() );

}

void CurlWrapper::injectGetParameters()
{
	bool includeAmp = false;
	getParameterValues = "";
	for( HttpParameter parameter : getParameterList )
	{
		if(includeAmp)
			getParameterValues.push_back('&');
		getParameterValues += parameter.getEscapedNameValue( curlHandle );
		includeAmp = true;
	}
}


std::string CurlWrapper::getParameterValuesAsUrl()
{
	if( getParameterValues.empty() )
	{
		return "";
	}
	else
	{
		return std::string("?") + getParameterValues;
	}
}



