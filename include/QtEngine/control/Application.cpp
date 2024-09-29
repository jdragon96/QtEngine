#include "QtEngine/control/Application.h"
#include <QLatin1String>

QtEngine::Application::Application(std::string themePath, int argc, char** argv, int flag) : QApplication(argc, argv, flag)
{
	if (themePath != "")
	{
		QFile file(QString::fromLocal8Bit(themePath.c_str()));
		if (!file.open(QFile::ReadOnly))
		{
			qWarning("Unable to open stylesheet file");
		}
		else
		{
			// 파일에서 스타일 시트 내용 읽어오기ￂ
			QString styleSheet = QLatin1String(file.readAll());
			// QApplication에 스타일 시트 설정
			this->setStyleSheet(styleSheet);
		}
	}
}