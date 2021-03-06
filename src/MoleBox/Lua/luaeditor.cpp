/*
    Copyright (c) 2012 Paul Brown <email>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/


#include "luaeditor.h"
#include "LuaScriptHelper.h"
#include "luascript.h"
#ifdef LUA_EDITOR

LuaHighlighter::LuaHighlighter(QObject* parent): QSyntaxHighlighter(parent)
{

}

LuaHighlighter::LuaHighlighter(QTextEdit* parent): QSyntaxHighlighter(parent)
{

}

LuaHighlighter::LuaHighlighter(QTextDocument* parent): QSyntaxHighlighter(parent)
{

}


void LuaHighlighter::highlightBlock(const QString& text)
{

     QTextCharFormat properties;
     properties.setForeground(Qt::black);
     QRegExp propertiesMatch("(\\.([a-zA-Z][a-zA-Z0-9])*)|(([a-zA-Z][a-zA-Z0-9])*\\()|[)+*-><]");
     
     
     QTextCharFormat function;
     function.setFontWeight(QFont::Bold);
     function.setForeground(Qt::black);
     QRegExp functionMatch("(function|end|if|then|local|do|repeat|while|return|nil|false|true|and|or|not)");
     
     QTextCharFormat number;
     number.setForeground(Qt::darkGreen);
     QRegExp numberMatch("[0-9]");

     QTextCharFormat string;
     string.setForeground(Qt::red);
     QRegExp stringMatch("\"[A-Za-z0-9_.]*\"");
     
     QTextCharFormat comment;
     comment.setForeground(Qt::gray);
     QRegExp commentMatch("--.*");
     int index;
     
     index = text.indexOf(propertiesMatch);
     while (index >= 0) {
         int length = propertiesMatch.matchedLength();
         setFormat(index, length, properties);
         index = text.indexOf(propertiesMatch, index + length);
     }     
          
     index = text.indexOf(functionMatch);
     while (index >= 0) {
         int length = functionMatch.matchedLength();
         setFormat(index, length, function);
         index = text.indexOf(functionMatch, index + length);
     }
     
     index = text.indexOf(numberMatch);
     while (index >= 0) {
         int length = numberMatch.matchedLength();
         setFormat(index, length, number);
         index = text.indexOf(numberMatch, index + length);
     }

     index = text.indexOf(stringMatch);
     while (index >= 0) {
         int length = stringMatch.matchedLength();
         setFormat(index, length, string);
         index = text.indexOf(stringMatch, index + length);
     }

     index = text.indexOf(commentMatch);
     while (index >= 0) {
         int length = commentMatch.matchedLength();
         setFormat(index, length, comment);
         index = text.indexOf(commentMatch, index + length);
     }     

          
}


LuaEditor::LuaEditor(QWidget *parent) : QWidget(parent)
{
  ui.setupUi(this);
  luaHighlight = new LuaHighlighter(ui.textEdit_code->document());
  
  QTextCharFormat format;
  format.setForeground(Qt::blue);
  ui.textEdit_code->setCurrentCharFormat(format);
  QApplication::connect( ui.comboBox_scriptSelection, SIGNAL(currentIndexChanged(QString)), this, SLOT(ChangeScript(QString)));
  QApplication::connect( ui.textEdit_code, SIGNAL(textChanged()), this, SLOT(UpdateScript()) ); // updates script on changes.
  connect(
        ui.listWidget_errors->model(),
       SIGNAL(rowsInserted ( const QModelIndex &, int, int ) ),
       ui.listWidget_errors,
       SLOT(scrollToBottom ())
    );
}

LuaEditor::~LuaEditor()
{

}

void LuaEditor::SetScripts( std::vector< std::string > scripts )
{
  
  this->scripts = scripts;    
  
  QStringList list;
  
  std::vector< std::string >::iterator itr;
  
  for (itr = scripts.begin(); itr != scripts.end(); itr++)
  {
    list << (*itr).c_str();
  }
  
  ui.comboBox_scriptSelection->addItems(list);
}


void LuaEditor::SetScript(std::string script)
{
  ui.textEdit_code->setText( script.c_str() );
    luaHighlight->rehighlight();
}

void LuaEditor::ChangeScript(QString scriptFile)
{
  
 std::string script = LuaHelper::LuaScripts::Instance().GrabScript(scriptFile.toStdString());
 
 ui.textEdit_code->setText( script.c_str() );
 luaHighlight->rehighlight();
 
}

void LuaEditor::UpdateScript()
{
  
  std::string scriptFile	= ui.comboBox_scriptSelection->itemText( ui.comboBox_scriptSelection->currentIndex() ).toStdString();
  
  std::string changedScript 	= ui.textEdit_code->toPlainText().toStdString();
  
  try {

    LuaScript script(true);
  
    bool success = script.LoadFromString(changedScript);
      script.RunScript();
      script.RunFunction("init");
      script.RunFunction("update");
      script.RunFunction("draw");
  
      LuaHelper::LuaScripts::Instance().UpdateScript( scriptFile, changedScript );
      
  }
  catch (std::string error) {
    
    this->ui.listWidget_errors->addItem(QString(error.c_str()));
    
  }


  
}

#endif
