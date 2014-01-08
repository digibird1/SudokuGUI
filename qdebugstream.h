/*
 * qdebugstream.h
 *
 *  Created on: Aug 5, 2012
 *      Author: Daniel Pelikan
 *
 *      Taken from a post of Jochen Ulrich
 *      http://lists.trolltech.com/qt-interest/2005-06/thread00166-0.html
 *
 */

#ifndef QDEBUGSTREAM_H_
#define QDEBUGSTREAM_H_

#include <iostream>
#include <streambuf>
#include <string>
#include <QtGui>
#include "qtextedit.h"

class QDebugStream : public std::basic_streambuf<char>
{
public:
 QDebugStream(std::ostream &stream, QTextEdit* text_edit, const QColor TextColor=Qt::black) : m_stream(stream),m_TextColor(TextColor)
 {
  log_window = text_edit;
  m_old_buf = stream.rdbuf();
  stream.rdbuf(this);
 }

private:
 void appendOwnText(const std::string &Text){
	 log_window->setTextColor(m_TextColor);
	 log_window->append(Text.c_str());
 }
public:
 ~QDebugStream()
 {
  // output anything that is left
  if (!m_string.empty())
	  appendOwnText(m_string);
   //log_window->append(m_string.c_str());

  m_stream.rdbuf(m_old_buf);
 }



protected:
 virtual int_type overflow(int_type v)
 {
  if (v == '\n')
  {
   //log_window->append(m_string.c_str());
   appendOwnText(m_string);
   m_string.erase(m_string.begin(), m_string.end());
  }
  else
   m_string += v;

  return v;
 }

 virtual std::streamsize xsputn(const char *p, std::streamsize n)
 {
  m_string.append(p, p + n);

  int pos = 0;
  while (pos != std::string::npos)
  {
   pos = m_string.find('\n');
   if (pos != std::string::npos)
   {
    std::string tmp(m_string.begin(), m_string.begin() + pos);
    //log_window->append(tmp.c_str());
    appendOwnText(tmp);

    m_string.erase(m_string.begin(), m_string.begin() + pos + 1);
   }
  }

  return n;
 }

private:
 std::ostream &m_stream;
 std::streambuf *m_old_buf;
 std::string m_string;
 QTextEdit* log_window;
 QColor m_TextColor;





};

#endif /* QDEBUGSTREAM_H_ */
