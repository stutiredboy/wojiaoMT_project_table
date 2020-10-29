
package gnet;

// {{{ RPCGEN_IMPORT_BEGIN
// {{{ DO NOT EDIT THIS
import com.locojoy.base.Marshal.OctetsStream;
import com.locojoy.base.Marshal.MarshalException;

abstract class __KeepAlive__ extends mkio.Protocol { }

/** client��glinkd֮���Э�� Э��ŷ�Χ[101,112],��ʷԭ����ЩЭ��Ų��ڸ÷�Χ
*/
// DO NOT EDIT THIS }}}
// RPCGEN_IMPORT_END }}}

public class KeepAlive extends __KeepAlive__ {
	@Override
	protected void process() {
		// protocol handle
		
		//��ʱ��û��ʵ�֣���ʱ��ʵ��
	}

	// {{{ RPCGEN_DEFINE_BEGIN
	// {{{ DO NOT EDIT THIS
	public static final int PROTOCOL_TYPE = 100;

	public int getType() {
		return 100;
	}

	public int code;

	public KeepAlive() {
	}

	public KeepAlive(int _code_) {
		this.code = _code_;
	}

	public final boolean _validator_() {
		return true;
	}

	public OctetsStream marshal(OctetsStream _os_) {
		_os_.marshal(code);
		return _os_;
	}

	public OctetsStream unmarshal(OctetsStream _os_) throws MarshalException {
		code = _os_.unmarshal_int();
		return _os_;
	}

	public boolean equals(Object _o1_) {
		if (_o1_ == this) return true;
		if (_o1_ instanceof KeepAlive) {
			KeepAlive _o_ = (KeepAlive)_o1_;
			if (code != _o_.code) return false;
			return true;
		}
		return false;
	}

	public int hashCode() {
		int _h_ = 0;
		_h_ += code;
		return _h_;
	}

	public String toString() {
		StringBuilder _sb_ = new StringBuilder();
		_sb_.append("(");
		_sb_.append(code).append(",");
		_sb_.append(")");
		return _sb_.toString();
	}

	public int compareTo(KeepAlive _o_) {
		if (_o_ == this) return 0;
		int _c_ = 0;
		_c_ = code - _o_.code;
		if (0 != _c_) return _c_;
		return _c_;
	}

	// DO NOT EDIT THIS }}}
	// RPCGEN_DEFINE_END }}}

}

