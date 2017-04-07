#include "NewBuildDialog.h"

bool NewBuildDialog::init() {
	if(!Layer::init()) {

		return false;
	}

	return true;
};

NewBuildDialog* NewBuildDialog::create() {

	NewBuildDialog* ret = new(std::nothrow) NewBuildDialog();
	if(ret && ret->init()) {
		ret->autorelease();
		return ret;
	}
	else {
		delete ret;
		ret = NULL;
		return NULL;
	}
};
