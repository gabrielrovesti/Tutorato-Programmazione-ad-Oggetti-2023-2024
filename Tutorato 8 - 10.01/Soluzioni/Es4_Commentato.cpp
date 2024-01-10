list<QCheckBox> Fun(vector<const QWidget*> &v, const QSize& sz){
    list<QCheckBox> ret;
    
    for(auto it = v.begin(); it!=v.end(); ++it){
        QAbstractSlider *qas = dynamic_cast<QAbstractSlider*>(const_cast<QWidget*>(*it));
        //const QAbstractSlider *qas = dynamic_cast<const QAbstractSlider*>(*it);
        if(qas){
            QSlider *qs = dynamic_cast<QAbstractSlider*>(const_cast<QWidget*>(*it));
            qs->resize(sz);
        }
        else{
            if (qs->size() != sz){
                qs->resize(sz);
                qs->setSliderDown(true);
            }
        }

        QAbstractButton *qab = dynamic_cast<QAbstractButton*>(const_cast<QWidget*>(*it));

        if(qab && qab->isDown()){
            QCheckBox *qcb = dynamic_cast<QCheckBox*>(const_cast<QWidget*>(*it));
            if(qcb)  ret.push_back(qcb);
            delete qcb;
            it = v.erase(it);
        }

    }
    return ret;
}