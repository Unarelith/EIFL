/*
 * =====================================================================================
 *
 *       Filename:  HtmlDelegate.hpp
 *
 *    Description:
 *
 *        Created:  04/12/2017 09:11:38
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef HTMLDELEGATE_HPP_
#define HTMLDELEGATE_HPP_

#include <QAbstractTextDocumentLayout>
#include <QApplication>
#include <QPainter>
#include <QStyle>
#include <QStyledItemDelegate>
#include <QTextDocument>

class HtmlDelegate : public QStyledItemDelegate {
	protected:
		void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
		QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex & index) const override;
};

void HtmlDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
	QStyleOptionViewItem options = option;
	initStyleOption(&options, index);

	QStyle *style = (options.widget) ? options.widget->style() : QApplication::style();

	QTextDocument doc;
	doc.setHtml(options.text);

	options.text = "";
	style->drawControl(QStyle::CE_ItemViewItem, &options, painter);

	QAbstractTextDocumentLayout::PaintContext ctx;
	if (option.state & QStyle::State_Selected)
		ctx.palette.setColor(QPalette::Text, options.palette.color(QPalette::Active, QPalette::HighlightedText));

	QSize iconSize = options.icon.actualSize(options.rect.size());
	QRect textRect = style->subElementRect(QStyle::SE_ItemViewItemText, &options);
	painter->save();
	painter->translate(textRect.left() + iconSize.width(), textRect.top());
	painter->setClipRect(textRect.translated(-(textRect.left() + iconSize.width()), -textRect.top()));
	doc.documentLayout()->draw(painter, ctx);
	painter->restore();
}

QSize HtmlDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
	QStyleOptionViewItem paintOption = option;
	initStyleOption(&paintOption, index);

	QTextDocument doc;
	doc.setHtml(paintOption.text);
	doc.setTextWidth(paintOption.rect.width());

	return QSize(doc.idealWidth(), doc.size().height());
}

#endif // HTMLDELEGATE_HPP_
