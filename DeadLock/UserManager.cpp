#include "UserManager.h"
#include "pch.h"
#include "AccountManager.h"
void UserManager::ProcessSave() {

	//accountLock
	lock_guard<mutex> guard(_mutex);

	Account* account = AccountManager::Instance()->GetAccount(100);

	//TODO
}