#ifndef _TWITCURL_H_
#define _TWITCURL_H_

#include <string>
#include <cstring>
#include "oauthlib.h"
#include "curl/curl.h"

/* Default values used in twitcurl */
namespace twitCurlDefaults
{
    /* Constants */
    const int TWITCURL_DEFAULT_BUFFSIZE = 1024;
    const std::string TWITCURL_COLON = ":";
    const char TWITCURL_EOS = '\0';

    /* Miscellaneous data used to build twitter URLs*/
    const std::string TWITCURL_STATUSSTRING = "status=";
    const std::string TWITCURL_TEXTSTRING = "text=";
    const std::string TWITCURL_QUERYSTRING = "query=";  
    const std::string TWITCURL_SEARCHQUERYSTRING = "?q=";      
    const std::string TWITCURL_SCREENNAME = "?screen_name=";
    const std::string TWITCURL_USERID = "?user_id=";
    const std::string TWITCURL_EXTENSIONFORMAT = ".xml";
    const std::string TWITCURL_TARGETSCREENNAME = "?target_screen_name=";
    const std::string TWITCURL_TARGETUSERID = "?target_id=";
    const std::string TWITCURL_SINCEID = "?since_id=";
};

/* Default twitter URLs */
namespace twitterDefaults
{

    /* Search URLs */
    const std::string TWITCURL_SEARCH_URL = "http://search.twitter.com/search.atom";

    /* Status URLs */
    const std::string TWITCURL_STATUSUPDATE_URL = "http://twitter.com/statuses/update.xml";
    const std::string TWITCURL_STATUSSHOW_URL = "http://twitter.com/statuses/show/";
    const std::string TWITCURL_STATUDESTROY_URL = "http://twitter.com/statuses/destroy/";

    /* Timeline URLs */
    const std::string TWITCURL_PUBLIC_TIMELINE_URL = "http://twitter.com/statuses/public_timeline.xml";
    const std::string TWITCURL_FEATURED_USERS_URL = "http://twitter.com/statuses/featured.xml";
    const std::string TWITCURL_FRIENDS_TIMELINE_URL = "http://twitter.com/statuses/friends_timeline.xml";
    const std::string TWITCURL_MENTIONS_URL = "http://twitter.com/statuses/mentions.xml";
    const std::string TWITCURL_USERTIMELINE_URL = "http://twitter.com/statuses/user_timeline.xml";

    /* Users URLs */
    const std::string TWITCURL_SHOWUSERS_URL = "http://twitter.com/users/show.xml";
    const std::string TWITCURL_SHOWFRIENDS_URL = "http://twitter.com/statuses/friends.xml";
    const std::string TWITCURL_SHOWFOLLOWERS_URL = "http://twitter.com/statuses/followers.xml";

    /* Direct messages URLs */
    const std::string TWITCURL_DIRECTMESSAGES_URL = "http://twitter.com/direct_messages.xml";
    const std::string TWITCURL_DIRECTMESSAGENEW_URL = "http://twitter.com/direct_messages/new.xml";
    const std::string TWITCURL_DIRECTMESSAGESSENT_URL = "http://twitter.com/direct_messages/sent.xml";
    const std::string TWITCURL_DIRECTMESSAGEDESTROY_URL = "http://twitter.com/direct_messages/destroy/";

    /* Friendships URLs */
    const std::string TWITCURL_FRIENDSHIPSCREATE_URL = "http://twitter.com/friendships/create.xml";
    const std::string TWITCURL_FRIENDSHIPSDESTROY_URL = "http://twitter.com/friendships/destroy.xml";
    const std::string TWITCURL_FRIENDSHIPSSHOW_URL = "http://twitter.com/friendships/show.xml";

    /* Social graphs URLs */
    const std::string TWITCURL_FRIENDSIDS_URL = "http://twitter.com/friends/ids.xml";
    const std::string TWITCURL_FOLLOWERSIDS_URL = "http://twitter.com/followers/ids.xml";

    /* Account URLs */
    const std::string TWITCURL_ACCOUNTRATELIMIT_URL = "http://twitter.com/account/rate_limit_status.xml";

    /* Favorites URLs */
    const std::string TWITCURL_FAVORITESGET_URL = "http://twitter.com/favorites.xml";
    const std::string TWITCURL_FAVORITECREATE_URL = "http://twitter.com/favorites/create/";
    const std::string TWITCURL_FAVORITEDESTROY_URL = "http://twitter.com/favorites/destroy/";

    /* Block URLs */
    const std::string TWITCURL_BLOCKSCREATE_URL = "http://twitter.com/blocks/create/";
    const std::string TWITCURL_BLOCKSDESTROY_URL = "http://twitter.com/blocks/destroy/";
    
    /* Saved Search URLs */
    const std::string TWITCURL_SAVEDSEARCHGET_URL = "http://twitter.com/saved_searches.xml";
    const std::string TWITCURL_SAVEDSEARCHSHOW_URL = "http://twitter.com/saved_searches/show/";
    const std::string TWITCURL_SAVEDSEARCHCREATE_URL = "http://twitter.com/saved_searches/create.xml";
    const std::string TWITCURL_SAVEDSEARCHDESTROY_URL = "http://twitter.com/saved_searches/destroy/";

    /* Trends URLs */
    const std::string TWITCURL_TRENDS_URL = "http://api.twitter.com/1/trends.json";
    const std::string TWITCURL_TRENDSDAILY_URL = "http://api.twitter.com/1/trends/daily.json";
    const std::string TWITCURL_TRENDSCURRENT_URL = "http://api.twitter.com/1/trends/current.json";
    const std::string TWITCURL_TRENDSWEEKLY_URL = "http://api.twitter.com/1/trends/weekly.json";
    const std::string TWITCURL_TRENDSAVAILABLE_URL = "http://api.twitter.com/1/trends/available.json";
    
};

/* twitCurl class */
class twitCurl
{
public:
    twitCurl();
    ~twitCurl();

    /* Twitter OAuth authorization methods */
    oAuth& getOAuth();
    bool oAuthRequestToken( std::string& authorizeUrl /* out */ );
    bool oAuthAccessToken();

    /* Twitter login APIs, set once and forget */
    std::string& getTwitterUsername();
    std::string& getTwitterPassword();
    void setTwitterUsername( std::string& userName /* in */ );
    void setTwitterPassword( std::string& passWord /* in */ );

    /* Twitter search APIs */
    bool search( std::string& query /* in */ );

    /* Twitter status APIs */
    bool statusUpdate( std::string& newStatus /* in */ );
    bool statusShowById( std::string& statusId /* in */ );
    bool statusDestroyById( std::string& statusId /* in */ );

    /* Twitter timeline APIs */
    bool timelinePublicGet();
    bool timelineFriendsGet();
    bool timelineUserGet( std::string userInfo = "" /* in */, bool isUserId = false /* in */ );
    bool featuredUsersGet();
    bool mentionsGet( std::string sinceId = "" /* in */ );

    /* Twitter user APIs */
    bool userGet( std::string& userInfo /* in */, bool isUserId = false /* in */ );
    bool friendsGet( std::string userInfo = "" /* in */, bool isUserId = false /* in */ );
    bool followersGet( std::string userInfo = "" /* in */, bool isUserId = false /* in */ );

    /* Twitter direct message APIs */
    bool directMessageGet();
    bool directMessageSend( std::string& userInfo /* in */, std::string& dMsg /* in */, bool isUserId = false /* in */ );
    bool directMessageGetSent();
    bool directMessageDestroyById( std::string& dMsgId /* in */ );

    /* Twitter friendships APIs */
    bool friendshipCreate( std::string& userInfo /* in */, bool isUserId = false /* in */ );
    bool friendshipDestroy( std::string& userInfo /* in */, bool isUserId = false /* in */ );
    bool friendshipShow( std::string& userInfo /* in */, bool isUserId = false /* in */ );

    /* Twitter social graphs APIs */
    bool friendsIdsGet( std::string& userInfo /* in */, bool isUserId = false /* in */ );
    bool followersIdsGet( std::string& userInfo /* in */, bool isUserId = false /* in */ );

    /* Twitter account APIs */
    bool accountRateLimitGet();

    /* Twitter favorites APIs */
    bool favoriteGet();
    bool favoriteCreate( std::string& statusId /* in */ );
    bool favoriteDestroy( std::string& statusId /* in */ );

    /* Twitter block APIs */
    bool blockCreate( std::string& userInfo /* in */ );
    bool blockDestroy( std::string& userInfo /* in */ );

    /* Twitter search APIs */
    bool savedSearchGet();
    bool savedSearchCreate( std::string& query /* in */ );
    bool savedSearchShow( std::string& searchId /* in */ );
    bool savedSearchDestroy( std::string& searchId /* in */ );

    /* Twitter trends APIs (JSON) */
    bool trendsGet();
    bool trendsDailyGet();
    bool trendsWeeklyGet();
    bool trendsCurrentGet();
    bool trendsAvailableGet();
    
    /* cURL APIs */
    bool isCurlInit();
    void getLastWebResponse( std::string& outWebResp /* out */ );
    void getLastCurlError( std::string& outErrResp /* out */);

    /* Internal cURL related methods */
    int saveLastWebResponse( char*& data, size_t size );
    static int curlCallback( char* data, size_t size, size_t nmemb, twitCurl* pTwitCurlObj );

    /* cURL proxy APIs */
    std::string& getProxyServerIp();
    std::string& getProxyServerPort();
    std::string& getProxyUserName();
    std::string& getProxyPassword();
    void setProxyServerIp( std::string& proxyServerIp /* in */ );
    void setProxyServerPort( std::string& proxyServerPort /* in */ );
    void setProxyUserName( std::string& proxyUserName /* in */ );
    void setProxyPassword( std::string& proxyPassword /* in */ );

private:
    /* cURL data */
    CURL* m_curlHandle;
    char m_errorBuffer[twitCurlDefaults::TWITCURL_DEFAULT_BUFFSIZE];
    std::string m_callbackData;

    /* cURL flags */
    bool m_curlProxyParamsSet;
    bool m_curlLoginParamsSet;
    bool m_curlCallbackParamsSet;

    /* cURL proxy data */
    std::string m_proxyServerIp;
    std::string m_proxyServerPort;
    std::string m_proxyUserName;
    std::string m_proxyPassword;

    /* Twitter data */
    std::string m_twitterUsername;
    std::string m_twitterPassword;

    /* OAuth data */
    oAuth m_oAuth;

    /* Private methods */
    void clearCurlCallbackBuffers();
    void prepareCurlProxy();
    void prepareCurlCallback();
    void prepareCurlUserPass();
    void prepareStandardParams();
    bool performGet( const std::string& getUrl );
    bool performGet( const std::string& getUrl, const std::string& oAuthHttpHeader );
    bool performDelete( const std::string& deleteUrl );
    bool performPost( const std::string& postUrl, std::string dataStr = "" );
};


/* Private functions */
void utilMakeCurlParams( std::string& outStr, std::string& inParam1, std::string& inParam2 );
void utilMakeUrlForUser( std::string& outUrl, const std::string& baseUrl, std::string& userInfo, bool isUserId );

#endif // _TWITCURL_H_
