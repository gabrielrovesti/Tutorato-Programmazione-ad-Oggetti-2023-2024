#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Widget {
private:
	int height;
	int width;
	bool visible;
public:
	Widget( int h, int w, bool v ) : height( h ), width( w ), visible( v ) {}
	virtual ~Widget() = 0;
	virtual void setStandardSize() = 0;
	void setHeight( int h ) { height = h; }
	void setWidth( int w ) { width = w; }
	void setVisible( bool v ) { visible = v; }
	int getHeight() const { return height; }
	int getWidth() const { return width; }
	bool isVisible() const { return visible; }
};

class AbstractButton : public Widget {
private:
	string label;
public:
	AbstractButton(int h, int w, bool v, string l = "") : Widget(h, w, v), label(l) {}
	void setLabel(string l) { label = l; }
	string getLabel() const { return label; }
};

class PushButton : public AbstractButton {
public:
	PushButton(int h, int w, bool v, string l) : AbstractButton( h, w, v, l ) {}
	virtual void setStandardSize() {
		setHeight(80);
		setWidth(20);
	}
};

class CheckBox : public AbstractButton {
private:
	bool checked;
public:
	CheckBox(int h, int w, bool v, string l, bool s) : AbstractButton(h, w, true, l), checked(s) {}
	void setCheckState(bool s) { checked = s; }
	bool isChecked() const { return checked; }
	void setStandardSize() {
		setHeight(5);
		setWidth(5);
	}
};


int main() {

}