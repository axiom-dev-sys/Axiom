class EditorLayer : public Layer
{
public:
    void onUpdate(float dt) override;
    void onRender() override;

private:
    EditorUI editorUI;
    EditorContext editorContext;

    HierarchyPanel hierarchyPanel;
    InspectorPanel inspectorPanel;
    SceneEditorPanel sceneEditorPanel;
    AssetBrowserPanel assetBrowserPanel;
    ConsolePanel consolePanel;
    StatisticsPanel statisticsPanel;
};