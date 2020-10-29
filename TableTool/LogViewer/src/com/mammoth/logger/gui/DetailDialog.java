package com.mammoth.logger.gui;

import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.SashForm;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Dialog;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.List;
import org.eclipse.swt.widgets.Shell;

public class DetailDialog extends Dialog {

	private List list;
	protected Object result;

	protected Shell shell;

	/**
	 * Create the dialog
	 * @param parent
	 * @param style
	 */
	public DetailDialog(Shell parent, int style) {
		super(parent, style);
	}

	/**
	 * Create the dialog
	 * @param parent
	 */
	public DetailDialog(Shell parent) {
		this(parent, SWT.NONE);
	}

	/**
	 * Open the dialog
	 * @return the result
	 */
	public Object open() {
		createContents();
		shell.open();
		shell.layout();
		Display display = getParent().getDisplay();
		while (!shell.isDisposed()) {
			if (!display.readAndDispatch())
				display.sleep();
		}
		return result;
	}

	/**
	 * Create contents of the dialog
	 */
	protected void createContents() {
		shell = new Shell(getParent(), SWT.DIALOG_TRIM | SWT.APPLICATION_MODAL);
		shell.setLayout(new FillLayout());
		shell.setSize(500, 375);
		shell.setText("�鿴����");

		final SashForm sashForm = new SashForm(shell, SWT.NONE);

		list = new List(sashForm, SWT.BORDER);
		list.setItems(new String[] {"0ʱ", "1ʱ", "2ʱ", "3ʱ", "4ʱ", "5ʱ", "6ʱ", "7ʱ", "8ʱ", "9ʱ", "10ʱ", "11ʱ", "12ʱ", "13ʱ", "14ʱ", "15ʱ", "16ʱ", "17ʱ", "18ʱ", "19ʱ", "20ʱ", "21ʱ", "22ʱ", "23ʱ"});

		new Composite(sashForm, SWT.NONE);
		sashForm.setWeights(new int[] {65, 426 });
		//
	}

}
