package AQSLTranspiler;

import javax.swing.*;
import javax.swing.text.*;
import java.awt.*;

public class SyntaxHighlighter {
    JTextPane textPane;
    DefaultStyledDocument defaultStyledDocument;
    Style style;

    public SyntaxHighlighter(JTextPane textPane){
        this.textPane = textPane;

        final StyleContext cont = StyleContext.getDefaultStyleContext();
        final AttributeSet attrCondition = cont.addAttribute(cont.getEmptySet(), StyleConstants.Foreground, Color.CYAN);
        final AttributeSet attrType = cont.addAttribute(cont.getEmptySet(), StyleConstants.Foreground, Color.GREEN);
        final AttributeSet attrSpecials = cont.addAttribute(cont.getEmptySet(), StyleConstants.Foreground, Color.YELLOW);
        final AttributeSet attrWhite = cont.addAttribute(cont.getEmptySet(), StyleConstants.Foreground, Color.WHITE);

        DefaultStyledDocument doc = new DefaultStyledDocument() {
            public void insertString (int offset, String str, AttributeSet a) throws BadLocationException {
                super.insertString(offset, str, a);

                String text = getText(0, getLength());
                int before = findLastNonWordChar(text, offset);
                if (before < 0) before = 0;
                int after = findFirstNonWordChar(text, offset + str.length());
                int wordL = before;
                int wordR = before;

                while (wordR <= after) {
                    if (wordR == after || String.valueOf(text.charAt(wordR)).matches("\\W")) {
                        if (text.substring(wordL, wordR).matches("(\\W)*(if|else if|else|out|in|uniform|layout)"))
                            setCharacterAttributes(wordL, wordR - wordL, attrCondition, false);
                        else if (text.substring(wordL, wordR).matches("(\\W)*(void|int|float|vec|vec2|vec3|vec4|mat|mat2|mat3|mat4)"))
                            setCharacterAttributes(wordL, wordR - wordL, attrType, false);
                        else if (text.substring(wordL, wordR).matches("(\\W)*(gl_Position|discard|texture|main)"))
                            setCharacterAttributes(wordL, wordR - wordL, attrSpecials, false);
                        else
                            setCharacterAttributes(wordL, wordR - wordL, attrWhite, false);
                        wordL = wordR;
                    }
                    wordR++;
                }
            }

            public void remove (int offs, int len) throws BadLocationException {
                super.remove(offs, len);

                String text = getText(0, getLength());
                int before = findLastNonWordChar(text, offs);
                if (before < 0) before = 0;
                int after = findFirstNonWordChar(text, offs);

                if (text.substring(before, after).matches("(\\W)*(private|public|protected)")) {
                    setCharacterAttributes(before, after - before, attrCondition, false);
                } else {
                    setCharacterAttributes(before, after - before, attrWhite, false);
                }
            }
        };
        textPane.setDocument(doc);
        defaultStyledDocument = (DefaultStyledDocument) textPane.getStyledDocument();
    }

    private int findLastNonWordChar (String text, int index) {
        while (--index >= 0) {
            if (String.valueOf(text.charAt(index)).matches("\\W")) {
                break;
            }
        }
        return index;
    }

    private int findFirstNonWordChar (String text, int index) {
        while (index < text.length()) {
            if (String.valueOf(text.charAt(index)).matches("\\W")) {
                break;
            }
            index++;
        }
        return index;
    }
}
