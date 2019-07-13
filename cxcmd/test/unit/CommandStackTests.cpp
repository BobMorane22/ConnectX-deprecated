#define GTEST_HAS_STD_TUPLE_ 1
#define GTEST_HAS_TR1_TUPLE  0

#include <gtest/gtest.h>

#include <cxcmd/include/CommandStack.h>

#include "CommandAddTwoMock.h"
#include "CommandTimesThreeMock.h"

namespace
{

constexpr size_t STACK_SIZE{ 200 };

} // namespace

TEST(CommandStack, Add_ValidCommand_CommandAdded)
{
    std::unique_ptr<cxcmd::ICommandStack> stack{new cxcmd::CommandStack(STACK_SIZE)};

    ASSERT_TRUE(stack);
    ASSERT_TRUE(stack->isEmpty());

    double result{0.0};

    std::unique_ptr<cxcmd::ICommand> cmd{new CommandAddTwoMock{result}};
    stack->add(std::move(cmd));

    ASSERT_FALSE(stack->isEmpty());
    ASSERT_EQ(stack->nbCommands(), 1);
}


TEST(CommandStack, Add_InvalidCommand_CommandNotAdded)
{
    std::unique_ptr<cxcmd::ICommandStack> stack{new cxcmd::CommandStack(STACK_SIZE)};

    ASSERT_TRUE(stack);
    ASSERT_TRUE(stack->isEmpty());

    double result{0.0};
    (void)result; // unused

    std::unique_ptr<cxcmd::ICommand> cmd;
    ASSERT_FALSE(cmd);

    stack->add(std::move(cmd));

    ASSERT_TRUE(stack->isEmpty());
}


TEST(CommandStack, Add_ManyValidCommands_CommandsAdded)
{
    std::unique_ptr<cxcmd::ICommandStack> stack{new cxcmd::CommandStack(STACK_SIZE)};

    ASSERT_TRUE(stack);
    ASSERT_TRUE(stack->isEmpty());

    double result{0.0};

    for(size_t index = 0; index < 5; ++index)
    {
        std::unique_ptr<cxcmd::ICommand> cmd{new CommandAddTwoMock{result}};
        stack->add(std::move(cmd));
    }

    ASSERT_FALSE(stack->isEmpty());
    ASSERT_EQ(stack->nbCommands(), 5);
}


TEST(CommandStack, Add_TooManyValidCommands_LastCommandIsLastInStack)
{
    std::unique_ptr<cxcmd::ICommandStack> stack{new cxcmd::CommandStack(STACK_SIZE)};

    ASSERT_TRUE(stack);
    ASSERT_TRUE(stack->isEmpty());

    double result{0.0};

    for(size_t index = 0; index < STACK_SIZE; ++index)
    {
        std::unique_ptr<cxcmd::ICommand> cmd{new CommandAddTwoMock{result}};
        cmd->execute();
        stack->add(std::move(cmd));
    }

    ASSERT_TRUE(stack->isFull());
    ASSERT_EQ(stack->nbCommands(), STACK_SIZE);
    ASSERT_EQ(result, 400.0);

    // Add one too many:
    std::unique_ptr<cxcmd::ICommand> cmd{new CommandTimesThreeMock{result}};
    cmd->execute();
    stack->add(std::move(cmd));

    ASSERT_TRUE(stack->isFull());
    ASSERT_EQ(stack->nbCommands(), STACK_SIZE);
    ASSERT_EQ(result, 1200.0);

    stack->undo();

    ASSERT_TRUE(stack->isFull());
    ASSERT_EQ(stack->nbCommands(), STACK_SIZE);
    ASSERT_EQ(result, 400.0);
}


TEST(CommandStack, Clear_SingleCommand_CommandCleared)
{
    std::unique_ptr<cxcmd::ICommandStack> stack{new cxcmd::CommandStack(STACK_SIZE)};

    ASSERT_TRUE(stack);
    ASSERT_TRUE(stack->isEmpty());

    double result{0.0};

    std::unique_ptr<cxcmd::ICommand> cmd{new CommandAddTwoMock{result}};
    stack->add(std::move(cmd));

    ASSERT_FALSE(stack->isEmpty());

    stack->clear();

    ASSERT_TRUE(stack->isEmpty());
}


TEST(CommandStack, Clear_ManyCommands_CommandsCleared)
{
    std::unique_ptr<cxcmd::ICommandStack> stack{new cxcmd::CommandStack(STACK_SIZE)};

    ASSERT_TRUE(stack);
    ASSERT_TRUE(stack->isEmpty());

    double result{0.0};

    for(size_t index = 0; index < 5; ++index)
    {
        std::unique_ptr<cxcmd::ICommand> cmd{new CommandAddTwoMock{result}};
        stack->add(std::move(cmd));
    }

    ASSERT_FALSE(stack->isEmpty());

    stack->clear();

    ASSERT_TRUE(stack->isEmpty());
}


TEST(CommandStack, Clear_NoCommand_NothingHappens)
{
    std::unique_ptr<cxcmd::ICommandStack> stack{new cxcmd::CommandStack(STACK_SIZE)};

    ASSERT_TRUE(stack);
    ASSERT_TRUE(stack->isEmpty());

    stack->clear();

    ASSERT_TRUE(stack->isEmpty());
}


TEST(CommandStack, Undo_SingleCommand_CommandUndoed)
{
    std::unique_ptr<cxcmd::ICommandStack> stack{new cxcmd::CommandStack(STACK_SIZE)};

    ASSERT_TRUE(stack);
    ASSERT_TRUE(stack->isEmpty());

    double result{0.0};

    std::unique_ptr<cxcmd::ICommand> cmd{new CommandAddTwoMock{result}};
    cmd->execute();

    ASSERT_EQ(result, 2.0);

    stack->add(std::move(cmd));
    stack->undo();

    ASSERT_EQ(result, 0.0);
}


TEST(CommandStack, Undo_MultipleCommands_AllCommandsUndoed)
{
    std::unique_ptr<cxcmd::ICommandStack> stack{new cxcmd::CommandStack(STACK_SIZE)};

    ASSERT_TRUE(stack);
    ASSERT_TRUE(stack->isEmpty());

    double result{0.0};

    std::unique_ptr<cxcmd::ICommand> cmd1{new CommandAddTwoMock{result}};
    std::unique_ptr<cxcmd::ICommand> cmd2{new CommandTimesThreeMock{result}};
    std::unique_ptr<cxcmd::ICommand> cmd3{new CommandAddTwoMock{result}};
    cmd1->execute();
    cmd2->execute();
    cmd3->execute();

    ASSERT_EQ(result, 8.0);

    stack->add(std::move(cmd1));
    stack->add(std::move(cmd2));
    stack->add(std::move(cmd3));

    stack->undo();
    stack->undo();
    stack->undo();

    ASSERT_EQ(result, 0.0);
}


TEST(CommandStack, Undo_NoCommand_NothingHappens)
{
    std::unique_ptr<cxcmd::ICommandStack> stack{new cxcmd::CommandStack(STACK_SIZE)};

    ASSERT_TRUE(stack);
    ASSERT_TRUE(stack->isEmpty());

    stack->undo();

    ASSERT_TRUE(stack->isEmpty());
}


TEST(CommandStack, Undo_TooManyUndoes_AllCommandsUndoed)
{
    ASSERT_TRUE(false);
}


TEST(CommandStack, Redo_SingleCommand_CommandRedoed)
{
    std::unique_ptr<cxcmd::ICommandStack> stack{new cxcmd::CommandStack(STACK_SIZE)};

    ASSERT_TRUE(stack);
    ASSERT_TRUE(stack->isEmpty());

    double result{0.0};

    std::unique_ptr<cxcmd::ICommand> cmd{new CommandAddTwoMock{result}};
    cmd->execute();

    ASSERT_EQ(result, 2.0);

    stack->add(std::move(cmd));
    stack->undo();
    stack->redo();

    ASSERT_EQ(result, 2.0);
}


TEST(CommandStack, Redo_MultipleCommands_AllCommandsRedoed)
{
    std::unique_ptr<cxcmd::ICommandStack> stack{new cxcmd::CommandStack(STACK_SIZE)};

    ASSERT_TRUE(stack);
    ASSERT_TRUE(stack->isEmpty());

    double result{0.0};

    std::unique_ptr<cxcmd::ICommand> cmd1{new CommandAddTwoMock{result}};
    std::unique_ptr<cxcmd::ICommand> cmd2{new CommandTimesThreeMock{result}};
    std::unique_ptr<cxcmd::ICommand> cmd3{new CommandAddTwoMock{result}};
    cmd1->execute();
    cmd2->execute();
    cmd3->execute();

    ASSERT_EQ(result, 8.0);

    stack->add(std::move(cmd1));
    stack->add(std::move(cmd2));
    stack->add(std::move(cmd3));

    stack->undo();
    stack->undo();
    stack->undo();

    stack->redo();
    stack->redo();
    stack->redo();

    ASSERT_EQ(result, 8.0);
}


TEST(CommandStack, Redo_NoCommand_NothingHappens)
{
    std::unique_ptr<cxcmd::ICommandStack> stack{new cxcmd::CommandStack(STACK_SIZE)};

    ASSERT_TRUE(stack);
    ASSERT_TRUE(stack->isEmpty());

    stack->redo();

    ASSERT_TRUE(stack->isEmpty());
}


TEST(CommandStack, Redo_TooManyRedoes_AllCommandsRedoed)
{
    ASSERT_TRUE(false);
}


TEST(CommandStack, UndoRedo_SingleCommand_StateIsUnchaged)
{
    ASSERT_TRUE(false);
}


TEST(CommandStack, UndoRedo_MultipleCommands_StateIsUnchaged)
{
    ASSERT_TRUE(false);
}
