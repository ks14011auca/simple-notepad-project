#ifndef SPELL_CHECKER_HIGHLIGHTER_H
#define SPELL_CHECKER_HIGHLIGHTER_H

#include "spell_checker.h"

#include <QColor>
#include <QRegularExpression>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QTextDocument>

class spell_checker_highlighter : public QSyntaxHighlighter {
public:
    explicit spell_checker_highlighter(QTextDocument* parent,
        const spell_checker& checker)
        : QSyntaxHighlighter(parent)
          , spelling_checker(checker)
    {
        misspelled_format.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);
        misspelled_format.setUnderlineColor(Qt::red);
    }

protected:
    void highlightBlock(const QString& text) override
    {
        static const QRegularExpression word_expression("[A-Za-z]+");

        auto matches = word_expression.globalMatch(text);
        while (matches.hasNext()) {
            const auto match = matches.next();
            const auto word = match.captured().toStdString();

            if (spelling_checker.is_misspelled(word)) {
                setFormat(match.capturedStart(), match.capturedLength(),
                    misspelled_format);
            }
        }
    }

private:
    const spell_checker& spelling_checker;
    QTextCharFormat misspelled_format;
};

#endif // SPELL_CHECKER_HIGHLIGHTER_H