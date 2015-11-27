#ifndef belcard_hpp
#define belcard_hpp

#include "belcard_generic.hpp"
#include "belcard_identification.hpp"

#include <string>
#include <list>
#include <map>
#include <memory>

using namespace::std;
using namespace::belr;

namespace belcard {
	class BelCard : public BelCardGeneric {
	private:
		shared_ptr<BelCardFN> _fn;
		shared_ptr<BelCardN> _n;
		shared_ptr<BelCardBirthday> _bday;
		shared_ptr<BelCardAnniversary> _anniversary;
		shared_ptr<BelCardGender> _gender;
		list<shared_ptr<BelCardNickname>> _nicknames;
		list<shared_ptr<BelCardPhoto>> _photos;
		list<shared_ptr<BelCardProperty>> _properties;
		
	public:
		static shared_ptr<BelCard> create() {
			return make_shared<BelCard>();
		}
		
		static void setHandlerAndCollectors(Parser<shared_ptr<BelCardGeneric>> *parser) {
			parser->setHandler("vcard", make_fn(&BelCard::create))
					->setCollector("FN", make_sfn(&BelCard::setFN))
					->setCollector("N", make_sfn(&BelCard::setN))
					->setCollector("BDAY", make_sfn(&BelCard::setBirthday))
					->setCollector("ANNIVERSARY", make_sfn(&BelCard::setAnniversary))
					->setCollector("GENDER", make_sfn(&BelCard::setGender))
					->setCollector("NICKNAME", make_sfn(&BelCard::addNickname))
					->setCollector("PHOTO", make_sfn(&BelCard::addPhoto));
		}
		
		BelCard() {
			
		}
		
		void setFN(const shared_ptr<BelCardFN> &fn) {
			_fn = fn;
			addProperty(_fn);
		}
		const shared_ptr<BelCardFN> &getFN() const {
			return _fn;
		}
		
		void setN(const shared_ptr<BelCardN> &n) {
			_n = n;
			addProperty(_n);
		}
		const shared_ptr<BelCardN> &getN() const {
			return _n;
		}
		
		void setBirthday(const shared_ptr<BelCardBirthday> &bday) {
			_bday = bday;
			addProperty(_bday);
		}
		const shared_ptr<BelCardBirthday> &getBirthday() const {
			return _bday;
		}
		
		void setAnniversary(const shared_ptr<BelCardAnniversary> &anniversary) {
			_anniversary = anniversary;
			addProperty(_anniversary);
		}
		const shared_ptr<BelCardAnniversary> &getAnniversary() const {
			return _anniversary;
		}
		
		void setGender(const shared_ptr<BelCardGender> &gender) {
			_gender = gender;
			addProperty(_gender);
		}
		const shared_ptr<BelCardGender> &getGender() const {
			return _gender;
		}
		
		void addNickname(const shared_ptr<BelCardNickname> &nickname) {
			_nicknames.push_back(nickname);
			addProperty(nickname);
		}
		const list<shared_ptr<BelCardNickname>> &getNicknames() const {
			return _nicknames;
		}
		
		void addPhoto(const shared_ptr<BelCardPhoto> &photo) {
			_photos.push_back(photo);
			addProperty(photo);
		}
		const list<shared_ptr<BelCardPhoto>> &getPhotos() const {
			return _photos;
		}
		
		void addProperty(const shared_ptr<BelCardProperty> &property) {
			_properties.push_back(property);
		}
		const list<shared_ptr<BelCardProperty>> &getProperties() const {
			return _properties;
		}
		
		string toString() {
			string vcard = "BEGIN:VCARD\r\nVERSION:4.0\r\n";
			for (auto it = _properties.begin(); it != _properties.end(); ++it) {
				vcard += (*it)->toString(); 
			}
			vcard += "END:VCARD\r\n";
			return vcard;
		}
	};	
}

#endif