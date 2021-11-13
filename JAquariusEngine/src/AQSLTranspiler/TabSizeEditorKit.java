package AQSLTranspiler;

import javax.swing.text.*;

/*
* @Mainly used for changing the default tab spacing.
* */
public class TabSizeEditorKit extends StyledEditorKit {

    public static final int TAB_SIZE=12;

    public ViewFactory getViewFactory() {
        return new MyViewFactory();
    }

    static class MyViewFactory implements ViewFactory {

        public View create(Element elem) {
            String kind = elem.getName();
            if (kind != null) {
                switch (kind) {
                    case AbstractDocument.ContentElementName:
                        return new LabelView(elem);
                    case AbstractDocument.ParagraphElementName:
                        return new CustomTabParagraphView(elem);
                    case AbstractDocument.SectionElementName:
                        return new BoxView(elem, View.Y_AXIS);
                    case StyleConstants.ComponentElementName:
                        return new ComponentView(elem);
                    case StyleConstants.IconElementName:
                        return new IconView(elem);
                }
            }

            return new LabelView(elem);
        }
    }

    static class CustomTabParagraphView extends ParagraphView {

        public CustomTabParagraphView(Element elem) {
            super(elem);
        }

        public float nextTabStop(float x, int tabOffset) {
            TabSet tabs = getTabSet();
            if(tabs == null) {
                // a tab every 72 pixels.
                return (float)(getTabBase() + (((int)x / TAB_SIZE + 1) * TAB_SIZE));
            }

            return super.nextTabStop(x, tabOffset);
        }

    }
}
