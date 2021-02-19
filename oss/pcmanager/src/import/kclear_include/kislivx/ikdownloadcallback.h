// 下载模块的回调。
#ifndef		_I_K_DOWNLOAD_CALL_BACK_H_ 
#define		_I_K_DOWNLOAD_CALL_BACK_H_ 
#include "kcallbackdatadef.h"



typedef enum
{
	EVT_K_DOWNLOAD_INIT_UI = 0,					//初始化UI。
	EVT_K_DOWNLOAD_INIT_ONE_FILE,				//初始化一个下载文件。
	EVT_K_DOWNLOAD_BEGIN,		
	EVT_K_DOWNLOAD_ONE_FILE_BEGIN,				// 下载一文件开始。
	EVT_K_DOWNLOAD_ONE_FILE_END,				// 下载一文件结束。
	EVT_K_DOWNLOAD_SUCCESSED,					//下载成功
	EVT_K_DOWNLOAD_FAILED,						//下载失败
	EVT_K_DOWNLOAD_START_DOWNLOADING,			//开始下载
	EVT_K_DOWNLOAD_GET_SIZEOF_FILE,				
	EVT_K_DOWNLOAD_PROCESS,						//下载进度
	EVT_K_DOWNLOAD_USER_BREAK,					//用户中断
	EVT_K_DOWNLOAD_CALLBACK_ALREADY_EXIST,		//下载回调已存在
	EVT_K_DOWNLOAD_USING_DEFAULT_BUFFER_SIZE,	//下载使用默认Buffer大小
	EVT_K_DOWNLOAD_PARAMETER_ERROR,				//下载参数有问题
	EVT_K_DOWNLOAD_PROXY_PARAMETER_ERROR,		//下载代理设置有问题
	EVT_K_DOWNLOAD_COMM_INIT_ERROR,				//下载初始化有问题
	EVT_K_DOWNLOAD_CONNECTING,					//下载连接中
	EVT_K_DOWNLOAD_CONNECT_SUCCESSED,			//下载连接成功
	EVT_K_DOWNLOAD_CONNECT_ERROR,				//下载连接失败
	EVT_K_DOWNLOAD_GET_IP_FROM_DNS,				//下载从DNS获取IP
	EVT_K_DOWNLOAD_SEND_REQUEST_ERROR,			//发送请求失败
	EVT_K_DOWNLOAD_PARSE_HTTP_HEADER_ERROR,		//解析Http头失败
	EVT_K_DOWNLOAD_HTTP_QUERY_INFO_ERROR,		//Http请求信息有问题
	EVT_K_DOWNLOAD_INTERNET_SET_OPTION_ERROR,	//网络设置有问题
	EVT_K_DOWNLOAD_AUTHENTICATION_DENIED,		//网络验证失败
	EVT_K_DOWNLOAD_PROXY_AUTHENTICATION_DENIED,	//代理验证失败
	EVT_K_DOWNLOAD_NEW_EVENT_PARAMS_ERROR,		
	EVT_K_DOWNLOAD_GET_SIZEOF_FILE_ERROR,		//获取文件大小失败
	EVT_K_DOWNLOAD_LOST_CONNECTION,				//下载失去连接
	EVT_K_DOWNLOAD_CREATE_FILE_ERROR,			//下载创建临时文件失败
	EVT_K_DOWNLOAD_DISK_FULL,					//下载磁盘空间满  提交用户是否需要继续，返回1 继续，0 不继续 
	EVT_K_DOWNLOAD_WRITE_FILE_ERROR,			//下载写文件错误
	EVT_K_DOWNLOAD_WRITE_PROTECTED,				//下载写文件保护
	EVT_K_DOWNLOAD_RETRY,						//下载重试

	EVT_K_DOWNLOAD_REMAIN_TIME						//下载剩余时间
} K_DOWNLOAD_EVT;



class IKDownloadCallBack
{
public:
	virtual int	OnDownloadEvent(K_DOWNLOAD_EVT nEvent, const KCallBackParam & stKCallBackParams = KCallBackParam()) = 0;
};

#endif		// #ifndef _I_K_DOWNLOAD_CALL_BACK_H_