	// Protocol

	enum { PROTOCOL_TYPE = 805460 };

	CMissionReachScene() {
		type = PROTOCOL_TYPE;
	}

	explicit CMissionReachScene(void *) : Protocol(PROTOCOL_TYPE) { } // define stub

	bool _validator_() const {
		return true;
	}

	FireNet::Marshal::OctetsStream & marshal(FireNet::Marshal::OctetsStream & _os_) const {
		if (!_validator_()) {
			throw Marshal::Exception();
		}
		return _os_;
	}

	const FireNet::Marshal::OctetsStream & unmarshal(const FireNet::Marshal::OctetsStream & _os_) {
		if (!_validator_()) {
			throw Marshal::Exception();
		}
		return _os_;
	}

	bool operator<(const CMissionReachScene &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const CMissionReachScene &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

	aio::Protocol * Clone() const { return new CMissionReachScene(*this); }
	int  PriorPolicy( ) const { return 1; }
	bool SizePolicy(size_t size) const { return size <= 65535; }