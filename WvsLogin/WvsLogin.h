#pragma once
#include "..\WvsLib\Net\WvsBase.h"
#include "..\WvsLib\Constants\WvsLoginConstants.hpp"
#include "Center.h"
#include <thread>
#include <mutex>
#include <condition_variable>

class WvsLogin : public WvsBase
{
private:
	void ConnectToCenter(int nCenterIdx);

	int m_nCenterCount = 0;
	std::shared_ptr<Center> aCenterList[ServerConstants::kMaxNumberOfCenters];
	std::shared_ptr<asio::io_service> aCenterServerService[ServerConstants::kMaxNumberOfCenters];
	std::shared_ptr<std::thread> aCenterWorkThread[ServerConstants::kMaxNumberOfCenters];

	//紀錄Center instance是否正在連線，用於避免重連的異常
	bool aIsConnecting[ServerConstants::kMaxNumberOfCenters];
	void CenterAliveMonitor(int idx);

public:

	WvsLogin();
	~WvsLogin();

	int GetCenterCount() const;
	std::shared_ptr<Center>& GetCenter(int idx);
	void InitializeCenter();
	void OnNotifySocketDisconnected(SocketBase *pSocket);

	//設定Center instance的連線狀況
	void SetCenterOpened(int nCenterIdx, bool bConnecting);

	//取得Center instance的連線狀況
	bool IsCenterOpened(int nCenterIdx) const;
};

