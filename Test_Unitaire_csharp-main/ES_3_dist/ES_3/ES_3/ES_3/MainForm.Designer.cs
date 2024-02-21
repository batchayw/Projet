namespace ES_3
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.CategorieProprieteComboBox = new System.Windows.Forms.ComboBox();
            this.CategorieProprieteLabel = new System.Windows.Forms.Label();
            this.ValeurFonciereLabel = new System.Windows.Forms.Label();
            this.ValeurFonciereTextBox = new System.Windows.Forms.TextBox();
            this.CalculerButton = new System.Windows.Forms.Button();
            this.TaxeFonciereTextBox = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // CategorieProprieteComboBox
            // 
            this.CategorieProprieteComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.CategorieProprieteComboBox.FormattingEnabled = true;
            this.CategorieProprieteComboBox.Items.AddRange(new object[] {
            "Résidence principale",
            "Résidence secondaire",
            "Terrain commercial",
            "Édifice commercial"});
            this.CategorieProprieteComboBox.Location = new System.Drawing.Point(149, 12);
            this.CategorieProprieteComboBox.Name = "CategorieProprieteComboBox";
            this.CategorieProprieteComboBox.Size = new System.Drawing.Size(227, 21);
            this.CategorieProprieteComboBox.TabIndex = 0;
            // 
            // CategorieProprieteLabel
            // 
            this.CategorieProprieteLabel.AutoSize = true;
            this.CategorieProprieteLabel.Location = new System.Drawing.Point(12, 15);
            this.CategorieProprieteLabel.Name = "CategorieProprieteLabel";
            this.CategorieProprieteLabel.Size = new System.Drawing.Size(117, 13);
            this.CategorieProprieteLabel.TabIndex = 1;
            this.CategorieProprieteLabel.Text = "Catégorie de propriété :";
            // 
            // ValeurFonciereLabel
            // 
            this.ValeurFonciereLabel.AutoSize = true;
            this.ValeurFonciereLabel.Location = new System.Drawing.Point(12, 43);
            this.ValeurFonciereLabel.Name = "ValeurFonciereLabel";
            this.ValeurFonciereLabel.Size = new System.Drawing.Size(99, 13);
            this.ValeurFonciereLabel.TabIndex = 2;
            this.ValeurFonciereLabel.Text = "Valeur foncière ($) :";
            // 
            // ValeurFonciereTextBox
            // 
            this.ValeurFonciereTextBox.Location = new System.Drawing.Point(149, 40);
            this.ValeurFonciereTextBox.Name = "ValeurFonciereTextBox";
            this.ValeurFonciereTextBox.Size = new System.Drawing.Size(227, 20);
            this.ValeurFonciereTextBox.TabIndex = 3;
            // 
            // CalculerButton
            // 
            this.CalculerButton.Location = new System.Drawing.Point(15, 76);
            this.CalculerButton.Name = "CalculerButton";
            this.CalculerButton.Size = new System.Drawing.Size(119, 23);
            this.CalculerButton.TabIndex = 4;
            this.CalculerButton.Text = "Calculer taxe foncière";
            this.CalculerButton.UseVisualStyleBackColor = true;
            this.CalculerButton.Click += new System.EventHandler(this.CalculerButton_Click);
            // 
            // TaxeFonciereTextBox
            // 
            this.TaxeFonciereTextBox.Location = new System.Drawing.Point(149, 79);
            this.TaxeFonciereTextBox.Name = "TaxeFonciereTextBox";
            this.TaxeFonciereTextBox.ReadOnly = true;
            this.TaxeFonciereTextBox.Size = new System.Drawing.Size(227, 20);
            this.TaxeFonciereTextBox.TabIndex = 5;
            this.TaxeFonciereTextBox.Text = "0.00 $";
            // 
            // MainForm
            // 
            this.AcceptButton = this.CalculerButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(388, 111);
            this.Controls.Add(this.TaxeFonciereTextBox);
            this.Controls.Add(this.CalculerButton);
            this.Controls.Add(this.ValeurFonciereTextBox);
            this.Controls.Add(this.ValeurFonciereLabel);
            this.Controls.Add(this.CategorieProprieteLabel);
            this.Controls.Add(this.CategorieProprieteComboBox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Calculateur de taxe foncière";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox CategorieProprieteComboBox;
        private System.Windows.Forms.Label CategorieProprieteLabel;
        private System.Windows.Forms.Label ValeurFonciereLabel;
        private System.Windows.Forms.TextBox ValeurFonciereTextBox;
        private System.Windows.Forms.Button CalculerButton;
        private System.Windows.Forms.TextBox TaxeFonciereTextBox;
    }
}

