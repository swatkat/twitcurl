#include "twitterClient.h"

void printUsage()
{
    printf( "\nUsage:\ntwitterClient -u username -p password\n" );
}

int main( int argc, char* argv[] )
{
    std::string userName( "" );
    std::string passWord( "" );
    if( argc > 4 )
    {
        for( int i = 1; i < argc; i += 2 )
        {
            if( 0 == strncmp( argv[i], "-u", strlen("-u") ) )
            {
                userName = argv[i+1];
            }
            else if( 0 == strncmp( argv[i], "-p", strlen("-p") ) )
            {
                passWord = argv[i+1];
            }
        }
        if( ( 0 == userName.length() ) || ( 0 == passWord.length() ) )
        {
            printUsage();
            return 0;
        }
    }
    else
    {
        printUsage();
        return 0;
    }

    twitCurl twitterObj;
    std::string tmpStr( "" );
    std::string replyMsg( "" );

    /* OAuth flow begins */
    /* Step 0: Set OAuth related params. These are got by registering your app at twitter.com */
    twitterObj.getOAuth().setConsumerKey( std::string( "vlC5S1NCMHHg8mD1ghPRkA" ) );
    twitterObj.getOAuth().setConsumerSecret( std::string( "3w4cIrHyI3IYUZW5O2ppcFXmsACDaENzFdLIKmEU84" ) );

    /* Step 1: Check if we alredy have OAuth access token from a previous run */
    char szKey[1024];
    std::string myOAuthAccessTokenKey("");
    std::string myOAuthAccessTokenSecret("");
	std::ifstream oAuthTokenKeyIn;
	std::ifstream oAuthTokenSecretIn;

    oAuthTokenKeyIn.open( "twitterClient_token_key.txt" );
    oAuthTokenSecretIn.open( "twitterClient_token_secret.txt" );

    memset( szKey, 0, 1024 );
    oAuthTokenKeyIn >> szKey;
    myOAuthAccessTokenKey = szKey;

    memset( szKey, 0, 1024 );
    oAuthTokenSecretIn >> szKey;
    myOAuthAccessTokenSecret = szKey;

    oAuthTokenKeyIn.close();
    oAuthTokenSecretIn.close();
    
    if( myOAuthAccessTokenKey.size() && myOAuthAccessTokenSecret.size() )
    {
        /* If we already have these keys, then no need to go through auth again */
        printf( "\nUsing:\nKey: %s\nSecret: %s\n\n", myOAuthAccessTokenKey.c_str(), myOAuthAccessTokenSecret.c_str() );

        twitterObj.getOAuth().setOAuthTokenKey( myOAuthAccessTokenKey );
        twitterObj.getOAuth().setOAuthTokenSecret( myOAuthAccessTokenSecret );
    }
    else
    {
        /* Step 2: Get request token key and secret */
        twitterObj.oAuthRequestToken( tmpStr );

        /* Step 3: Ask user to visit web link and get PIN */
        char szOAuthVerifierPin[1024];
        memset( szOAuthVerifierPin, 0, 1024 );
        printf( "\nPlease visit this link in web browser and authorize this application:\n%s", tmpStr.c_str() );
        printf( "\nEnter the PIN provided by twitter: " );
        gets( szOAuthVerifierPin );
        tmpStr = szOAuthVerifierPin;
        twitterObj.getOAuth().setOAuthPin( tmpStr );

        /* Step 4: Exchange request token with access token */
        twitterObj.oAuthAccessToken();

        /* Step 5: Now, save this access token key and secret for future use without PIN */
        twitterObj.getOAuth().getOAuthTokenKey( myOAuthAccessTokenKey );
        twitterObj.getOAuth().getOAuthTokenSecret( myOAuthAccessTokenSecret );

        /* Step 6: Save these keys in a file or wherever */
		std::ofstream oAuthTokenKeyOut;
		std::ofstream oAuthTokenSecretOut;

        oAuthTokenKeyOut.open( "twitterClient_token_key.txt" );
        oAuthTokenSecretOut.open( "twitterClient_token_secret.txt" );

        oAuthTokenKeyOut.clear();
        oAuthTokenSecretOut.clear();

        oAuthTokenKeyOut << myOAuthAccessTokenKey.c_str();
        oAuthTokenSecretOut << myOAuthAccessTokenSecret.c_str();

        oAuthTokenKeyOut.close();
        oAuthTokenSecretOut.close();
    }
    /* OAuth flow ends */

    /* Set twitter username and password */
    twitterObj.setTwitterUsername( userName );
    twitterObj.setTwitterPassword( passWord );

    /* Set proxy server usename, password, IP and port (if present) */
    char proxyPresent[1024];
    memset( proxyPresent, 0, 1024 );

    printf( "\nDo you have a proxy server configured (0 for no; 1 for yes): " );
    gets( proxyPresent );
    int isProxy = atoi( proxyPresent );

    if( isProxy > 0 )
    {
        char proxyIp[1024];
        char proxyPort[1024];
        char proxyUsername[1024];
        char proxyPassword[1024];

        memset( proxyIp, 0, 1024 );
        memset( proxyPort, 0, 1024 );
        memset( proxyUsername, 0, 1024 );
        memset( proxyPassword, 0, 1024 );

        printf( "\nEnter proxy server IP: " );
        gets( proxyIp );
        printf( "\nEnter proxy server port: " );
        gets( proxyPort );
        printf( "\nEnter proxy server username: " );
        gets( proxyUsername );
        printf( "\nEnter proxy server password: " );
        gets( proxyPassword );

        tmpStr = proxyIp;
        twitterObj.setProxyServerIp( tmpStr );
        tmpStr = proxyPort;
        twitterObj.setProxyServerPort( tmpStr );
        tmpStr = proxyUsername;
        twitterObj.setProxyUserName( tmpStr );
        tmpStr = proxyPassword;
        twitterObj.setProxyPassword( tmpStr );
    }

    /* Post a new status message */
    char statusMsg[1024];
    memset( statusMsg, 0, 1024 );
    printf( "\nEnter a new status message: " );
    gets( statusMsg );
    tmpStr = statusMsg;
    replyMsg = "";
    if( twitterObj.statusUpdate( tmpStr ) )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::statusUpdate web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::statusUpdate error:\n%s\n", replyMsg.c_str() );
    }

    /* Destroy a status message */
    memset( statusMsg, 0, 1024 );
    printf( "\nEnter status message id to delete: " );
    gets( statusMsg );
    tmpStr = statusMsg;
    replyMsg = "";
    if( twitterObj.statusDestroyById( tmpStr ) )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::statusDestroyById web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::statusDestroyById error:\n%s\n", replyMsg.c_str() );
    }

    /* Get user timeline */
    replyMsg = "";
    printf( "\nGetting user timeline\n" );
    if( twitterObj.timelineUserGet( true ) )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::timelineUserGet web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::timelineUserGet error:\n%s\n", replyMsg.c_str() );
    }

    /* Get public timeline */
    replyMsg = "";
    printf( "\nGetting public timeline\n" );
    if( twitterObj.timelinePublicGet() )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::timelinePublicGet web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::timelinePublicGet error:\n%s\n", replyMsg.c_str() );
    }

    /* Get friend ids */
    replyMsg = "";
    printf( "\nGetting friend ids\n" );
    tmpStr = "techcrunch";
    if( twitterObj.friendsIdsGet( tmpStr, false ) )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::friendsIdsGet web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::friendsIdsGet error:\n%s\n", replyMsg.c_str() );
    }

    /* Get trends */
    if( twitterObj.trendsDailyGet() )
    {
        twitterObj.getLastWebResponse( replyMsg );
        printf( "\ntwitterClient:: twitCurl::trendsDailyGet web response:\n%s\n", replyMsg.c_str() );
    }
    else
    {
        twitterObj.getLastCurlError( replyMsg );
        printf( "\ntwitterClient:: twitCurl::trendsDailyGet error:\n%s\n", replyMsg.c_str() );
    }

    return 0;
}