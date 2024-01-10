list<QCheckBox> Fun(vector<const QWidget*>& v, const QSize& sz){
	list<QCheckBox> res;
	for (auto it = v.begin(); it != v.end()){
		QAbstractSlider* s = dynamic_cast<QAbstractSlider*>(const_cast<QWidget*>(*it));
		
		if (s){
			if (!dynamic_cast<QSlider*>(s)){
				delete s;
				s = new QSlider();
				s->resize(sz);
			} else {
				if (s->size() != sz){
					s->resize(sz);
					s->setSliderDown(true);
				}
			}
			it++;
		} else {
			QAbstractButton* b = dynamic_cast<QAbstractButton*>(const_cast<QWidget*>(*it));
			
			if (b && b->isDown()){
				QCheckBox* cb = dynamic_cast<QCheckBox*>(b);
				if (cb) res.push_back(*cb);
				delete b;
				it = v.erase(it);
			} else it++;
		
		} 	
	}
	
	return res;
}
